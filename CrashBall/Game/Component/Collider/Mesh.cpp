#include "pch.h"
#include "Mesh.h"

#include <fstream>

using namespace nlohmann;

/**
 * コンストラクタ
 * 
 */
Mesh::Mesh(IGameObject* owner)
	: Collider(owner, ColliderType::Mesh)
{
}

/**
 * データの読み込み
 * 
 * \param filename データのファイル名
 */
void Mesh::LoadJson(const wchar_t* fileName, float scale)
{
	std::ifstream ifs(fileName);

	if (!ifs.is_open()) {
		return;
	}

	json data;

	ifs >> data;

	for (auto& face : data["Face"])
	{
		m_faces.push_back(
			std::make_unique<Triangle>(face, scale)
		);
	}

	ifs.close();
}
