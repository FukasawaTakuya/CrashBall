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

using namespace DirectX;

RegisterComponent(Mesh)

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
 * \brief デストラクタ
 *
 */
Mesh::~Mesh()
{
}

/**
 * \brief アタッチ時の処理
 * 
 */
void Mesh::Awake()
{
	Collider::Awake();

	//LoadJson(m_meshData);

	m_modelRenderer = GetGameObject()->GetComponent<ModelRenderer>();
}

/**
 * \brief 開始処理
 * 
 * \param gameContext
 */
void Mesh::Start(const GameContext& gameContext)
{
	if (m_modelRenderer != nullptr)
	{
		CreateMesh();
	}
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


/**
 * \brief メッシュの生成
 * 
 */
void Mesh::CreateMesh()
{
	auto& indexList = m_modelRenderer->GetModel()->GetIndexList();
	auto& vertexList = m_modelRenderer->GetModel()->GetVertexList();
	SimpleMath::Vector3 scale = m_transform->GetWorldScale();
	for (int i = 0; i < indexList.size(); i += 3)
	{
		auto vertex0 = vertexList[i];
		auto vertex1 = vertexList[i + 1];
		auto vertex2 = vertexList[i + 2];

		Triangle t;
		t.SetTriangle(vertex0.position, vertex1.position, vertex2.position);

		m_faces.push_back(std::make_unique<Triangle>(t, scale));

	}
}
