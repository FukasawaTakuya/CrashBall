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

		if (type == L"VS")
		{
			// 入力レイアウトの作成
			D3D11_INPUT_ELEMENT_DESC inputDesc[] =
			{
				{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
				{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
				{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,	0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
			};
			DX::ThrowIfFailed(
				device->CreateInputLayout(
					inputDesc,
					_countof(inputDesc),
					shaderInfo.blob->GetBufferPointer(),
					shaderInfo.blob->GetBufferSize(),
					shaderInfo.inputLayout.ReleaseAndGetAddressOf()));
		}

		// コンテナに格納
		m_shaders.emplace(key, std::move(shaderInfo));
	}
}

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

