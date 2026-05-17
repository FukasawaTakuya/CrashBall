#include "pch.h"
#include "Mesh.h"

#include <fstream>
#include <sstream>
#include <string>
#include "Game/CollisionManager/Collision.h"

using namespace nlohmann;

/**
 * コンストラクタ
 * 
 */
Mesh::Mesh()
	: Collider(ColliderType::Mesh)
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

	for (auto face : data["Face"])
	{
		m_faces.push_back(
			std::make_unique<Triangle>(face, scale)
		);
	}

	ifs.close();
}

/**
 * \brief 回転
 * 
 * \param rotate 回転行列
 */
void Mesh::Rotate(DirectX::SimpleMath::Matrix rotate)
{
	for (auto& face : m_faces) {
		face->Rotate(rotate, m_position);
	}
}
