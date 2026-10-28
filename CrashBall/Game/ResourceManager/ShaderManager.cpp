/*****************************************************************//**
 * \file   ShaderManager.cpp
 * \brief  シェーダ管理クラス
 *
 * \author 深沢拓矢
 * \date   October 2026
 *********************************************************************/

#include "pch.h"
#include "ShaderManager.h"
#include "Game/Common/Utility.h"

/**
 * \brief コンストラクタ
 * 
 */
ShaderManager::ShaderManager()
{
}

/**
 * \brief シェーダの作成
 * 
 * \param device デバイス
 */
void ShaderManager::CreateShader(ID3D11Device1* device)
{
	for (auto& file : std::filesystem::directory_iterator("Resources/Shader"))
	{
		ShaderInfo shaderInfo;

		// ワイド文字に変換
		std::wstring path = Utility::ConvertToWideChar(file.path().string());

		// バイナリ情報の読み込み
		D3DReadFileToBlob(
			path.c_str(),
			shaderInfo.blob.ReleaseAndGetAddressOf());

		size_t pos = path.rfind(L".") - 2;

		std::wstring type = path.substr(pos, 2).c_str();
		if (type == L"VS")
			shaderInfo.shader = Microsoft::WRL::ComPtr<ID3D11VertexShader>();
		else if (type == L"PS")
			shaderInfo.shader = Microsoft::WRL::ComPtr<ID3D11PixelShader>();

		// シェーダの作成
		std::visit([&](auto& shader)
			{
				using T = std::decay_t<decltype(shader)>;

				if constexpr (std::is_same_v<T, Microsoft::WRL::ComPtr<ID3D11VertexShader>>)
				{
					device->CreateVertexShader(
						shaderInfo.blob->GetBufferPointer(),
						shaderInfo.blob->GetBufferSize(),
						nullptr,
						shader.ReleaseAndGetAddressOf());
				}
				if constexpr (std::is_same_v<T, Microsoft::WRL::ComPtr<ID3D11PixelShader>>)
				{
					device->CreatePixelShader(
						shaderInfo.blob->GetBufferPointer(),
						shaderInfo.blob->GetBufferSize(),
						nullptr,
						shader.ReleaseAndGetAddressOf());
				}
			}, shaderInfo.shader);


		// キーを抽出
		size_t end = file.path().string().rfind(".");
		size_t start = file.path().string().rfind("Shader") + 7;
		std::string key = file.path().string().substr(start, end - start);

		// 定数バッファの作成
		CreateConstatBuffer(shaderInfo, device);

		// 入力レイアウトの作成
		CreateInputLayout(shaderInfo, device);

		// コンテナに格納
		m_shaders.emplace(key, std::move(shaderInfo));
	}
}

/**
 * \brief 定数バッファの作成
 * 
 * \param shaderInfo シェーダ情報
 * \param device デバイス
 */
void ShaderManager::CreateConstatBuffer(ShaderInfo& shaderInfo, ID3D11Device1* device)
{
	Microsoft::WRL::ComPtr<ID3D11ShaderReflection> reflection;

	// リフレクション
	DX::ThrowIfFailed(
		D3DReflect(
			shaderInfo.blob->GetBufferPointer(),
			shaderInfo.blob->GetBufferSize(),
			IID_ID3D11ShaderReflection,
			reinterpret_cast<void**>(reflection.GetAddressOf())));

	// シェーダ情報
	D3D11_SHADER_DESC shaderDesc;
	DX::ThrowIfFailed(reflection->GetDesc(&shaderDesc));

	for (int i = 0; i < shaderDesc.ConstantBuffers; i++)
	{
		auto refcb = reflection->GetConstantBufferByIndex(i);

		// 定数バッファの情報
		D3D11_SHADER_BUFFER_DESC cbDesc{};
		if (FAILED(refcb->GetDesc(&cbDesc)))
		{
			continue;
		}

		// バインド情報
		D3D11_SHADER_INPUT_BIND_DESC bindDesc{};
		if (FAILED(reflection->GetResourceBindingDescByName(
			cbDesc.Name, &bindDesc)))
		{
			continue;
		}

		if (bindDesc.Type == D3D_SIT_CBUFFER)
		{
			ConstantBufferResource constantBuffer;

			// 定数バッファ情報を取得
			constantBuffer.info.name = cbDesc.Name;
			constantBuffer.info.size = cbDesc.Size;
			constantBuffer.info.registerSlot = bindDesc.BindPoint;
			constantBuffer.info.data.resize(constantBuffer.info.size, std::byte{ 0 });

			// 定数バッファの作成
			D3D11_BUFFER_DESC bufDesc = {};
			bufDesc.Usage = D3D11_USAGE_DYNAMIC;
			bufDesc.ByteWidth = cbDesc.Size;
			bufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			bufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			bufDesc.MiscFlags = 0;
			bufDesc.StructureByteStride = 0;
			device->CreateBuffer(&bufDesc, nullptr, constantBuffer.buffer.ReleaseAndGetAddressOf());

			for (int j = 0; j < cbDesc.Variables; j++)
			{
				// 変数情報
				auto variable = refcb->GetVariableByIndex(j);
				D3D11_SHADER_VARIABLE_DESC varDesc;
				variable->GetDesc(&varDesc);

				ShaderVariableInfo shaderVariableInfo{};

				shaderVariableInfo.name = varDesc.Name;
				shaderVariableInfo.size = varDesc.Size;
				shaderVariableInfo.offset = varDesc.StartOffset;

				constantBuffer.info.variables.push_back(shaderVariableInfo);
			}

			shaderInfo.constantBuffer.push_back(std::move(constantBuffer));
		}
	}
}

/**
 * \brief 入力レイアウトの作成
 * 
 * \param shaderInfo シェーダ情報
 * \param device デバイス
 */
void ShaderManager::CreateInputLayout(ShaderInfo& shaderInfo, ID3D11Device1* device)
{
	Microsoft::WRL::ComPtr<ID3D11ShaderReflection> reflection;

	// リフレクション
	DX::ThrowIfFailed(
		D3DReflect(
			shaderInfo.blob->GetBufferPointer(),
			shaderInfo.blob->GetBufferSize(),
			IID_ID3D11ShaderReflection,
			reinterpret_cast<void**>(reflection.GetAddressOf())));

	// シェーダ情報
	D3D11_SHADER_DESC shaderDesc;
	DX::ThrowIfFailed(reflection->GetDesc(&shaderDesc));

	std::vector<D3D11_INPUT_ELEMENT_DESC> inputDesc(shaderDesc.InputParameters);
	for (int i = 0; i < shaderDesc.InputParameters; i++)
	{
		// パラメータ情報
		D3D11_SIGNATURE_PARAMETER_DESC paramDesc{};
		reflection->GetInputParameterDesc(i, &paramDesc);

		inputDesc[i].SemanticName = paramDesc.SemanticName;
		inputDesc[i].SemanticIndex = paramDesc.SemanticIndex;
		inputDesc[i].InputSlot = 0;
		inputDesc[i].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		inputDesc[i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputDesc[i].InstanceDataStepRate = 0;

		// 要素数
		UINT componentCount = 0;
		if (paramDesc.Mask & 0x1) componentCount++;
		if (paramDesc.Mask & 0x2) componentCount++;
		if (paramDesc.Mask & 0x4) componentCount++;
		if (paramDesc.Mask & 0x8) componentCount++;

		// 要素数とデータ型をもとにフォーマットを求める
		switch (paramDesc.ComponentType)
		{
		case D3D_REGISTER_COMPONENT_FLOAT32:
			switch (componentCount)
			{
			case 1: inputDesc[i].Format = DXGI_FORMAT_R32_FLOAT;
				break;
			case 2: inputDesc[i].Format = DXGI_FORMAT_R32G32_FLOAT;
				break;
			case 3: inputDesc[i].Format = DXGI_FORMAT_R32G32B32_FLOAT;
				break;
			case 4: inputDesc[i].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
				break;
			}
			break;

		case D3D_REGISTER_COMPONENT_SINT32:
			switch (componentCount)
			{
			case 1: inputDesc[i].Format = DXGI_FORMAT_R32_SINT;
				break;
			case 2: inputDesc[i].Format = DXGI_FORMAT_R32G32_SINT;
				break;
			case 3: inputDesc[i].Format = DXGI_FORMAT_R32G32B32_SINT;
				break;
			case 4: inputDesc[i].Format = DXGI_FORMAT_R32G32B32A32_SINT;
				break;
			}
			break;

		case D3D_REGISTER_COMPONENT_UINT32:
			switch (componentCount)
			{
			case 1: inputDesc[i].Format = DXGI_FORMAT_R32_UINT;
				break;
			case 2: inputDesc[i].Format = DXGI_FORMAT_R32G32_UINT;
				break;
			case 3: inputDesc[i].Format = DXGI_FORMAT_R32G32B32_UINT;
				break;
			case 4: inputDesc[i].Format = DXGI_FORMAT_R32G32B32A32_UINT;
				break;
			}
			break;
		}
	}

	// 入力レイアウトの作成
	DX::ThrowIfFailed(
		device->CreateInputLayout(
			inputDesc.data(),
			inputDesc.size(),
			shaderInfo.blob->GetBufferPointer(),
			shaderInfo.blob->GetBufferSize(),
			shaderInfo.inputLayout.ReleaseAndGetAddressOf()));
}

