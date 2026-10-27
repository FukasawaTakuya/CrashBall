#include "pch.h"
#include "Shader.h"

#include <d3dcompiler.h>

/**
 * \brief コンストラクタ
 * 
 */
Shader::Shader()
{
}

void Shader::UpdateSubResources(ID3D11DeviceContext1* context)
{
	for (auto& cbInfo : m_constantInfo)
	{
		D3D11_MAPPED_SUBRESOURCE subResource{};
		context->Map(cbInfo.gpuBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
		memcpy(subResource.pData, cbInfo.data.data(), cbInfo.size);
		context->Unmap(cbInfo.gpuBuffer.Get(), 0);
	}
}

void Shader::Bind(ID3D11DeviceContext1* context)
{

	std::visit([&](const auto& shader)
		{
			if constexpr (std::is_same_v<std::decay_t<decltype(shader)>, Microsoft::WRL::ComPtr<ID3D11VertexShader>>)
			{
				for (auto& cbInfo : m_constantInfo)
				{
					ID3D11Buffer* bufferptr = cbInfo.gpuBuffer.Get();
					context->VSSetConstantBuffers(
						cbInfo.registerSlot,
						1,
						&bufferptr);
				}
				context->VSSetShader(shader.Get(), nullptr, 0);
			}
			if constexpr (std::is_same_v<std::decay_t<decltype(shader)>, Microsoft::WRL::ComPtr<ID3D11PixelShader>>)
			{
				for (auto& cbInfo : m_constantInfo)
				{
					ID3D11Buffer* bufferptr = cbInfo.gpuBuffer.Get();
					context->PSSetConstantBuffers(
						cbInfo.registerSlot,
						1,
						&bufferptr);
				}
				context->PSSetShader(shader.Get(), nullptr, 0);
			}
		}, m_shader);
}

/**
 * \brief シェーダの作成(頂点シェーダ)
 * 
 * \param shader 格納先
 * \param filePath ファイルパス
 * \param device デバイス
 * \return 
 */
ShaderVariant Shader::CreateShader(
	Microsoft::WRL::ComPtr<ID3D11VertexShader>& shader, 
	const std::wstring& filePath, 
	ID3D11Device1* device)
{
	DX::ThrowIfFailed(
		device->CreateVertexShader(
			m_blob->GetBufferPointer(),
			m_blob->GetBufferSize(),
			nullptr,
			shader.ReleaseAndGetAddressOf()));

	return std::move(shader);
}

/**
 * \brief シェーダの作成(ピクセルシェーダ)
 *
 * \param shader 格納先
 * \param filePath ファイルパス
 * \param device デバイス
 * \return
 */
ShaderVariant Shader::CreateShader(
	Microsoft::WRL::ComPtr<ID3D11PixelShader>& shader,
	const std::wstring& filePath,
	ID3D11Device1* device)
{
	DX::ThrowIfFailed(
		device->CreatePixelShader(
			m_blob->GetBufferPointer(),
			m_blob->GetBufferSize(),
			nullptr,
			shader.ReleaseAndGetAddressOf()));

	return std::move(shader);
}

void Shader::Create(ID3D11Device1* device)
{
	// シェーダの作成
	std::visit([&, this](auto& shader)
		{
			// 頂点シェーダ
			if constexpr (std::is_same_v<std::decay_t<decltype(shader)>, Microsoft::WRL::ComPtr<ID3D11VertexShader>>)
			{
				DX::ThrowIfFailed(
					device->CreateVertexShader(
						m_blob->GetBufferPointer(),
						m_blob->GetBufferSize(),
						nullptr,
						shader.ReleaseAndGetAddressOf()));
			}
			// ピクセルシェーダ
			if constexpr (std::is_same_v<std::decay_t<decltype(shader)>, Microsoft::WRL::ComPtr<ID3D11PixelShader>>)
			{
				DX::ThrowIfFailed(
					device->CreatePixelShader(
						m_blob->GetBufferPointer(),
						m_blob->GetBufferSize(),
						nullptr,
						shader.ReleaseAndGetAddressOf()));
			}
		}, m_shader);

	// リフレクション
	DX::ThrowIfFailed(
		D3DReflect(
			m_blob->GetBufferPointer(),
			m_blob->GetBufferSize(),
			IID_ID3D11ShaderReflection,
			reinterpret_cast<void**>(m_reflection.GetAddressOf())));

	// シェーダ情報
	D3D11_SHADER_DESC shaderDesc;
	DX::ThrowIfFailed(m_reflection->GetDesc(&shaderDesc));

	for (int i = 0; i < shaderDesc.ConstantBuffers; i++)
	{
		auto cb = m_reflection->GetConstantBufferByIndex(i);

		// 定数バッファの情報
		D3D11_SHADER_BUFFER_DESC cbDesc{};
		if (FAILED(cb->GetDesc(&cbDesc)))
		{
			continue;
		}

		D3D11_SHADER_INPUT_BIND_DESC bindDesc{};
		if (FAILED(m_reflection->GetResourceBindingDescByName(
			cbDesc.Name, &bindDesc)))
		{
			continue;
		}

		ConstantBufferInfo cbInfo{};

		// 定数バッファ情報
		cbInfo.name = cbDesc.Name;
		cbInfo.size = cbDesc.Size;
		cbInfo.registerSlot = bindDesc.BindPoint;
		cbInfo.data.resize(cbInfo.size, std::byte{ 0 });

		// 定数バッファの作成
		D3D11_BUFFER_DESC bufDesc = {};
		bufDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufDesc.ByteWidth = cbDesc.Size;
		bufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufDesc.MiscFlags = 0;
		bufDesc.StructureByteStride = 0;
		device->CreateBuffer(&bufDesc, nullptr, cbInfo.gpuBuffer.ReleaseAndGetAddressOf());

		for (int j = 0; j < cbDesc.Variables; j++)
		{
			// 変数情報
			auto variable = cb->GetVariableByIndex(j);
			D3D11_SHADER_VARIABLE_DESC varDesc;
			variable->GetDesc(&varDesc);

			ShaderVariableInfo shaderVariableInfo{};

			shaderVariableInfo.name = varDesc.Name;
			shaderVariableInfo.size = varDesc.Size;
			shaderVariableInfo.offset = varDesc.StartOffset;

			cbInfo.variables.push_back(shaderVariableInfo);
		}

		m_constantInfo.push_back(std::move(cbInfo));
	}
}

