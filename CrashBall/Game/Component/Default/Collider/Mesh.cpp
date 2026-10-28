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

	LoadJson(m_meshData);

	m_modelRenderer = GetGameObject()->GetComponent<ModelRenderer>();

	if (m_modelRenderer != nullptr)
	{
		CalcBoudingRadius();
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
 * \brief 三角形ポリゴンの取得
 * 
 * \param index
 * \return 
 */
Triangle Mesh::GetTriangle(int index)
{
	auto& indexList = m_modelRenderer->GetModel()->GetIndexList();
	auto& vertexList = m_modelRenderer->GetModel()->GetVertexList();

	index = indexList[index];

	auto vertex0 = vertexList[index];
	auto vertex1 = vertexList[index + 1];
	auto vertex2 = vertexList[index + 2];

	Triangle triangle;

	triangle.SetTriangle(vertex0.position, vertex1.position, vertex2.position);
	triangle.Rotate(m_transform->GetWorldRotate(), m_transform->GetWorldPosition());
	triangle.Scale(m_transform->GetWorldScale());

	return triangle;
}

/**
 * \brief 境界球の半径を求める
 * 
 */
void Mesh::CalcBoudingRadius()
{
	m_boundingRadius.clear();
	auto& indexList = m_modelRenderer->GetModel()->GetIndexList();
	auto& vertexList = m_modelRenderer->GetModel()->GetVertexList();
	for (int i = 0; i < indexList.size(); i += 3)
	{
		auto vertex0 = vertexList[i];
		auto vertex1 = vertexList[i + 1];
		auto vertex2 = vertexList[i + 2];

		DirectX::SimpleMath::Vector3 center
		{
			(vertex0.position.x + vertex1.position.x + vertex2.position.x) / 3,
			(vertex0.position.y + vertex1.position.y + vertex2.position.y) / 3,
			(vertex0.position.z + vertex1.position.z + vertex2.position.z) / 3,
		};

		SimpleMath::Vector3 v0 = vertex0.position - center;
		SimpleMath::Vector3 v1 = vertex1.position - center;
		SimpleMath::Vector3 v2 = vertex2.position - center;

		float boudingSphere
			= std::sqrtf(
				std::max(std::max(v0.LengthSquared(),
					v1.LengthSquared()),
					v2.LengthSquared()));

		m_boundingRadius.push_back(boudingSphere);
	}
}
