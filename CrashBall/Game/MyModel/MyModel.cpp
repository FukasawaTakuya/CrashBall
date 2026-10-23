#include "pch.h"
#include "MyModel.h"

#include <fstream>
#include "WICTextureLoader.h"
#include "DX/ReadData.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 */
MyModel::MyModel()
{
}

/**
 * \brief 描画
 * 
 * \param world
 * \param view
 * \param proj
 * \param states
 * \param context
 */
void MyModel::Draw(
	const DirectX::SimpleMath::Matrix& world, 
	const DirectX::SimpleMath::Matrix& view, 
	const DirectX::SimpleMath::Matrix& proj, 
	DirectX::CommonStates* states, 
	ID3D11DeviceContext1* context)
{
	// =========== IA =========== //

	// 頂点バッファの設定
	ID3D11Buffer* vBuffers[] = { m_vertexBuffer.Get() };
	UINT strides[] = { sizeof(Vertex) };
	UINT offset[] = { 0 };
	context->IASetVertexBuffers(0, 1, vBuffers, strides, offset);
	// インデックスバッファの設定
	context->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	// トポロジーの設定
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// 入力レイアウトの設定
	context->IASetInputLayout(m_inputLayout.Get());

	//  ==== 定数バッファの更新 ==== //
	D3D11_MAPPED_SUBRESOURCE subResource;

	// 頂点シェーダ
	ConstantVS cbufVS{};
	cbufVS.worldViewProj = world * view * proj;
	XMStoreFloat4x4(&cbufVS.worldInvertTranspose, XMMatrixTranspose(XMMatrixInverse(nullptr, world)));
	cbufVS.lightDirection = XMFLOAT4(0.0f, -1.0f, 1.0f, 1.0f);
	// 書き込み
	context->Map(m_constantVS.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
	memcpy(subResource.pData, &cbufVS, sizeof(ConstantVS));
	context->Unmap(m_constantVS.Get(), 0);

	ID3D11Buffer* constantVS = m_constantVS.Get();
	context->VSSetConstantBuffers(0, 1, &constantVS);

	// ==== 頂点シェーダの設定 ==== //
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);

	// ==== ピクセルシェーダの設定 ==== //
	context->PSSetShader(m_pixeShader.Get(), nullptr, 0);
	// サンプラーをシェーダに渡す
	auto sampler = states->LinearClamp();
	context->PSSetSamplers(0, 1, &sampler);

	// ==== RS ==== //
	context->RSSetState(states->CullNone());

	// ==== OM ==== //
	// 深度ステンシルステートの設定
	context->OMSetDepthStencilState(states->DepthDefault(), 0);
	// ブレンドステートの設定
	context->OMSetBlendState(states->NonPremultiplied(), nullptr, 0xffffffff);

	for (auto& submesh : m_submeshList)
	{
		// ==== 定数バッファの設定 ==== //
		ConstantPS cbufPS{};
		MaterialData mat = m_materialDataList[submesh.materialIndex];
		cbufPS.baseColor = mat.baseColor;
		cbufPS.textureIndex.x = mat.textureIndex;
		// 書き込み
		context->Map(m_constantPS.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
		memcpy(subResource.pData, &cbufPS, sizeof(ConstantPS));
		context->Unmap(m_constantPS.Get(), 0);
		ID3D11Buffer* constantPS = m_constantPS.Get();
		context->PSSetConstantBuffers(1, 1, &constantPS);

		// テクスチャをシェーダに渡す
		ID3D11ShaderResourceView* srv = nullptr;
		if (mat.textureIndex >= 0)
		{
			srv = m_textureList[mat.textureIndex].Get();
		}
		context->PSSetShaderResources(0, 1, &srv);

		// 描画
		context->DrawIndexed(submesh.indexCount, submesh.indexStart, 0);
	}
}

/**
 * \brief モデルの作成
 * 
 * \param filepath
 */
void MyModel::Create(
	ID3D11Device1* device,
	const std::string& filepath)
{
	std::ifstream ifs(filepath, std::ios::binary);

	if (!ifs.is_open())
	{
		OutputDebugStringA("ファイルが開けませんでした\n");
		return;
	}

	// ヘッダーの読み込み
	ModelHeader header;
	ifs.read(
		reinterpret_cast<char*>(&header),
		sizeof(ModelHeader));

	// 頂点の読み込み
	m_vertexList.resize(header.vertexCount);
	ifs.read(
		reinterpret_cast<char*>(m_vertexList.data()),
		sizeof(Vertex) * m_vertexList.size());

	// インデックスの読み込み
	m_indexList.resize(header.indexCount);
	ifs.read(
		reinterpret_cast<char*>(m_indexList.data()),
		sizeof(uint32_t) * m_indexList.size());

	// サブメッシュの読み込み
	m_submeshList.resize(header.submeshCount);
	ifs.read(
		reinterpret_cast<char*>(m_submeshList.data()),
			sizeof(Submesh) * m_submeshList.size());

	// マテリアルの読み込み
	m_materialDataList.resize(header.materialCount);
	ifs.read(
		reinterpret_cast<char*>(m_materialDataList.data()),
		sizeof(MaterialData) * m_materialDataList.size());

	// テクスチャの読み込み
	std::vector<std::vector<uint8_t>> textureBinaryList;
	for (int i = 0; i < header.textureCount; i++)
	{
		// テクスチャサイズ
		uint64_t size;
		ifs.read(
			reinterpret_cast<char*>(&size),
			sizeof(uint64_t));

		std::vector<uint8_t> texture(size);
		ifs.read(
			reinterpret_cast<char*>(texture.data()),
			sizeof(uint8_t) * texture.size());

		textureBinaryList.push_back(texture);
	}

	// 頂点バッファの作成
	{
		D3D11_BUFFER_DESC desc{};
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(Vertex) * m_vertexList.size();
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA initData{};
		initData.pSysMem = m_vertexList.data();
		initData.SysMemPitch = 0;
		initData.SysMemSlicePitch = 0;

		DX::ThrowIfFailed(
			device->CreateBuffer(&desc, &initData, m_vertexBuffer.ReleaseAndGetAddressOf()));
	}

	// インデックスバッファの作成
	{
		D3D11_BUFFER_DESC desc{};
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(uint32_t) * m_indexList.size();
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA initData{};
		initData.pSysMem = m_indexList.data();
		initData.SysMemPitch = 0;
		initData.SysMemSlicePitch = 0;

		DX::ThrowIfFailed(
			device->CreateBuffer(&desc, &initData, m_indexBuffer.ReleaseAndGetAddressOf()));
	}

	// テクスチャの作成
	for (auto& texData : textureBinaryList)
	{
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;

		DX::ThrowIfFailed(
			CreateWICTextureFromMemory(
				device,
				texData.data(),
				texData.size(),
				nullptr,
				texture.ReleaseAndGetAddressOf()));

		m_textureList.push_back(std::move(texture));
	}

	// 頂点シェーダの作成
	std::vector<uint8_t> vs_data = DX::ReadData(L"Resources/Shader/Basic_VS.cso");
	DX::ThrowIfFailed(
		device->CreateVertexShader(vs_data.data(), vs_data.size(), nullptr, m_vertexShader.ReleaseAndGetAddressOf()));

	// ピクセルシェーダの作成
	std::vector<uint8_t> ps_data = DX::ReadData(L"Resources/Shader/Basic_PS.cso");
	DX::ThrowIfFailed(
		device->CreatePixelShader(ps_data.data(), ps_data.size(), nullptr, m_pixeShader.ReleaseAndGetAddressOf()));

	// 定数バッファの作成
	{
		D3D11_BUFFER_DESC desc = {};
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;    
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;  
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;

		// 頂点シェーダー用
		desc.ByteWidth = sizeof(ConstantVS);
		DX::ThrowIfFailed(
			device->CreateBuffer(&desc, nullptr, m_constantVS.ReleaseAndGetAddressOf()));

		// ピクセルシェーダー用
		desc.ByteWidth = sizeof(ConstantPS);
		DX::ThrowIfFailed(
			device->CreateBuffer(&desc, nullptr, m_constantPS.ReleaseAndGetAddressOf()));
	}

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
			vs_data.data(),
			vs_data.size(),
			m_inputLayout.ReleaseAndGetAddressOf()));
}
