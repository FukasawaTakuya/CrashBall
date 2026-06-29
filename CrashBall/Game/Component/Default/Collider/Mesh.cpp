/*****************************************************************//**
 * \file   Mesh.cpp
 * \brief  メッシュコライダー
 *
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#include "pch.h"
#include "Mesh.h"

#include <fstream>

using namespace nlohmann;
using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 */
Mesh::Mesh(IGameObject* gameObject)
	: Collider(gameObject, ColliderType::Mesh)
{
}

/**
 * \brief コピーコンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 * \param mesh メッシュコライダー
 */
Mesh::Mesh(
	IGameObject* gameObject, 
	const Mesh& mesh)
	: Collider(gameObject, ColliderType::Mesh)
	, m_meshData(mesh.m_meshData)
{
	LoadJson(m_meshData);
}

/**
 * \brief デストラクタ
 *
 */
Mesh::~Mesh()
{
}

/**
 * \brief データの読み込み
 *
 * \param filename データのファイル名
 */
void Mesh::LoadJson(const std::string& fileName)
{
	std::ifstream ifs(fileName);

	if (!ifs.is_open()) {
		return;
	}

	m_meshData = fileName;

	SimpleMath::Vector3 scale = m_transform->GetWorldScale();

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

/**
 * \brief 回転
 * 
 */
void Mesh::Rotate()
{
	for (auto& face : m_faces)
	{
		face->Rotate(m_transform->GetWorldRotate(), m_transform->GetWorldPosition());
	}
}
