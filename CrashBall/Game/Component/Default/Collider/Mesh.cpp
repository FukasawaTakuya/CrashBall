#include "pch.h"
#include "Mesh.h"

#include <fstream>

using namespace nlohmann;

/**
 * \brief コンストラクタ
 * 
 */
Mesh::Mesh(IGameObject* owner)
	: Collider(owner, ColliderType::Mesh)
{
}

/**
 * \brief データの読み込み
 * 
 * \param filename データのファイル名
 */
void Mesh::LoadJson(const wchar_t* fileName)
{
	std::ifstream ifs(fileName);

	float scale = m_transform->GetScale();

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
