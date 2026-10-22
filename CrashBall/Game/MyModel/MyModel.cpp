#include "pch.h"
#include "MyModel.h"

#include <fstream>
#include "WICTextureLoader.h"
#include "DX/ReadData.h"

using namespace DirectX;

MyModel::MyModel()
{
}

void MyModel::Draw(
	const DirectX::SimpleMath::Matrix& world, 
	const DirectX::SimpleMath::Matrix& view, 
	const DirectX::SimpleMath::Matrix& proj, 
	DirectX::CommonStates* states, 
	ID3D11DeviceContext1* context)
{
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
	std::vector<Vertex> vertexList(header.vertexCount);
	ifs.read(
		reinterpret_cast<char*>(vertexList.data()),
		sizeof(Vertex) * header.vertexCount);

	// インデックスの読み込み
	std::vector<uint32_t> indexList(header.indexCount);
	ifs.read(
		reinterpret_cast<char*>(indexList.data()),
		header.indexCount);

	// サブメッシュの読み込み
	m_submeshList.resize(header.submeshCount);
	ifs.read(
		reinterpret_cast<char*>(m_submeshList.data()),
			sizeof(Submesh) * header.submeshCount);

	// マテリアルの読み込み
	m_materialDataList.resize(header.materialCount);
	ifs.read(
		reinterpret_cast<char*>(m_materialDataList.data()),
		sizeof(MaterialData) * header.materialCount);

	// テクスチャの読み込み
	std::vector<std::vector<uint8_t>> textureList;
	for (int i = 0; i < header.textureCount; i++)
	{
		uint64_t size;

		ifs.read(
			reinterpret_cast<char*>(&size),
			sizeof(uint64_t));

		std::vector<uint8_t> texture(size);
		ifs.read(
			reinterpret_cast<char*>(texture.data()),
			size);

		textureList.push_back(texture);
	}

	// 頂点バッファの作成
	{
		D3D11_BUFFER_DESC desc{};
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(Vertex) * vertexList.size();
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA initData{};
		initData.pSysMem = vertexList.data();
		initData.SysMemPitch = 0;
		initData.SysMemSlicePitch = 0;

		DX::ThrowIfFailed(
			device->CreateBuffer(&desc, &initData, m_vertexBuffer.ReleaseAndGetAddressOf()));
	}

	// インデックスバッファの作成
	{
		D3D11_BUFFER_DESC desc{};
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = indexList.size();
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA initData{};
		initData.pSysMem = indexList.data();
		initData.SysMemPitch = 0;
		initData.SysMemSlicePitch = 0;

		DX::ThrowIfFailed(
			device->CreateBuffer(&desc, &initData, m_indexBuffer.ReleaseAndGetAddressOf()));
	}

	// テクスチャの作成
	for (auto& texData : textureList)
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

	// 入力レイアウトの作成
	D3D11_INPUT_ELEMENT_DESC inputDesc[] = 
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	DX::ThrowIfFailed(
		device->CreateInputLayout(
			inputDesc,
			_countof(inputDesc),
			vs_data.data(),
			vs_data.size(),
			m_inputLayout.ReleaseAndGetAddressOf()));
}
