#include "pch.h"
#include "MyModel.h"

#include <fstream>

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
void MyModel::Create(const std::string& filepath)
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
	std::vector<std::vector<uint32_t>> textureList;
	for (int i = 0; i < header.textureCount; i++)
	{
		uint64_t size;

		ifs.read(
			reinterpret_cast<char*>(&size),
			sizeof(uint64_t));

		std::vector<uint32_t> texture(size);
		ifs.read(
			reinterpret_cast<char*>(texture.data()),
			size);

		textureList.push_back(texture);
	}

}
