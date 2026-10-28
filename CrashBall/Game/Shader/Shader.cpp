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

/**
 * \brief サブリソースの更新
 * 
 * \param context デバイスコンテキスト
 */
void Shader::UpdateSubResources(ID3D11DeviceContext1* context)
{
	for (auto& constantBuffer : m_constantBuffer)
	{
		D3D11_MAPPED_SUBRESOURCE subResource{};
		context->Map(constantBuffer.buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
		memcpy(subResource.pData, constantBuffer.info.data.data(), constantBuffer.info.size);
		context->Unmap(constantBuffer.buffer, 0);
	}
}

/**
 * \brief シェーダのバインド
 * 
 * \param context デバイスコンテキスト
 */
void Shader::Bind(ID3D11DeviceContext1* context)
{
	std::visit([&](const auto& shader)
		{
			using shaderType = std::decay_t<decltype(shader)>;

			if constexpr (std::is_same_v<shaderType, ID3D11VertexShader*>)
			{
				for (auto& constantBuffer : m_constantBuffer)
				{
					context->VSSetConstantBuffers(
						constantBuffer.info.registerSlot,
						1,
						&constantBuffer.buffer);
				}
				context->VSSetShader(shader, nullptr, 0);
			}
			if constexpr (std::is_same_v<shaderType, ID3D11PixelShader*>)
			{
				for (auto& constantBuffer : m_constantBuffer)
				{
					context->PSSetConstantBuffers(
						constantBuffer.info.registerSlot,
						1,
						&constantBuffer.buffer);
				}
				context->PSSetShader(shader, nullptr, 0);
			}
		}, m_shader);
}

/**
 * \brief シェーダの設定
 * 
 * \param shaderInfo
 */
void Shader::SetShader(const ShaderInfo* shaderInfo)
{
	m_constantBuffer.clear();

	// シェーダのポインタを格納
	std::visit([&](auto& shader)
		{
			m_shader = shader.Get();
		}, shaderInfo->shader);

	// バイナリ情報のポインタを格納
	m_blob = shaderInfo->blob.Get();

	for (auto& cb : shaderInfo->constantBuffer)
	{
		// 定数バッファはポインタを格納し定数バッファ情報はコピー
		m_constantBuffer.emplace_back(cb.buffer.Get(), cb.info);
	}

	// 入力レイアウトのポインタを格納
	m_inputLayout = shaderInfo->inputLayout.Get();
}

//void Shader::Create(ID3D11Device1* device)
//{
//	Microsoft::WRL::ComPtr<ID3D11ShaderReflection> reflection;
//
//	// リフレクション
//	DX::ThrowIfFailed(
//		D3DReflect(
//			m_blob->GetBufferPointer(),
//			m_blob->GetBufferSize(),
//			IID_ID3D11ShaderReflection,
//			reinterpret_cast<void**>(reflection.GetAddressOf())));
//
//	// シェーダ情報
//	D3D11_SHADER_DESC shaderDesc;
//	DX::ThrowIfFailed(reflection->GetDesc(&shaderDesc));
//
//	for (int i = 0; i < shaderDesc.ConstantBuffers; i++)
//	{
//		auto cb = reflection->GetConstantBufferByIndex(i);
//
//		// 定数バッファの情報
//		D3D11_SHADER_BUFFER_DESC cbDesc{};
//		if (FAILED(cb->GetDesc(&cbDesc)))
//		{
//			continue;
//		}
//
//		D3D11_SHADER_INPUT_BIND_DESC bindDesc{};
//		if (FAILED(reflection->GetResourceBindingDescByName(
//			cbDesc.Name, &bindDesc)))
//		{
//			continue;
//		}
//
//		if (bindDesc.Type == D3D_SIT_CBUFFER)
//		{
//			ConstantBufferInfo cbInfo{};
//
//			// 定数バッファ情報
//			cbInfo.name = cbDesc.Name;
//			cbInfo.size = cbDesc.Size;
//			cbInfo.registerSlot = bindDesc.BindPoint;
//			cbInfo.data.resize(cbInfo.size, std::byte{ 0 });
//
//			// 定数バッファの作成
//			D3D11_BUFFER_DESC bufDesc = {};
//			bufDesc.Usage = D3D11_USAGE_DYNAMIC;
//			bufDesc.ByteWidth = cbDesc.Size;
//			bufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//			bufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
//			bufDesc.MiscFlags = 0;
//			bufDesc.StructureByteStride = 0;
//			device->CreateBuffer(&bufDesc, nullptr, cbInfo.gpuBuffer.ReleaseAndGetAddressOf());
//
//			for (int j = 0; j < cbDesc.Variables; j++)
//			{
//				// 変数情報
//				auto variable = cb->GetVariableByIndex(j);
//				D3D11_SHADER_VARIABLE_DESC varDesc;
//				variable->GetDesc(&varDesc);
//
//				ShaderVariableInfo shaderVariableInfo{};
//
//				shaderVariableInfo.name = varDesc.Name;
//				shaderVariableInfo.size = varDesc.Size;
//				shaderVariableInfo.offset = varDesc.StartOffset;
//
//				cbInfo.variables.push_back(shaderVariableInfo);
//			}
//
//			m_constantInfo.push_back(std::move(cbInfo));
//		}
//	}
//}

