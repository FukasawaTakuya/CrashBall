/*****************************************************************//**
 * \file   Mesh.cpp
 * \brief  メッシュコライダー
 *
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#include "pch.h"
#include "Mesh.h"
#include "Game/Json/JsonDeserializers.h"

#include <fstream>

using namespace nlohmann;

/**
 * \brief コンストラクタ
 * 
 */
Mesh::Mesh(IGameObject* gameObject)
	: Collider(gameObject, ColliderType::Mesh)
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
