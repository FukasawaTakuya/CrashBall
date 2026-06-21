/*****************************************************************//**
 * \file   ResolveCollisionTable.cpp
 * \brief  衝突解決関数テーブル 
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#include "pch.h"
#include "ResolveCollisionTable.h"

/**
 * \brief コンストラクタ
 * 
 */
ResolveCollisionTable::ResolveCollisionTable()
{
	// 衝突解決関数テーブルの登録
	m_table[ToInt(ColliderType::Sphere)]
		[ToInt(ColliderType::Sphere)]
		= SphereVsSphere;

	m_table[ToInt(ColliderType::Sphere)]
		[ToInt(ColliderType::Mesh)]
		= SphereVsMesh;

	m_table[ToInt(ColliderType::Mesh)]
		[ToInt(ColliderType::Sphere)]
		= SphereVsMesh;

	//m_table[ToInt(ColliderType::Mesh)]
	//	[ToInt(ColliderType::Mesh)]
	//	= MeshVsMesh;
}

/**
 * \brief デストラクタ
 * 
 */
ResolveCollisionTable::~ResolveCollisionTable()
{
}

/**
 * \brief 衝突解決
 * 
 * \param col1 コライダー1
 * \param col2 コライダー2
 */
void ResolveCollisionTable::ResolveCollision(Collider* col1, Collider* col2)
{
	// コライダーのタイプが大きい方をcol2にする
	if (col1->GetType() > col2->GetType())
		std::swap(col1, col2);

	// 関数テーブルに登録されていない組み合わせならリターン
	if (m_table[ToInt(col1->GetType())][ToInt(col2->GetType())] == nullptr)
	{
		return;
	}

	// 関数テーブルから関数を呼び出す
	m_table[ToInt(col1->GetType())][ToInt(col2->GetType())](col1, col2);
}

/**
 * \brief 球対球の衝突解決
 * 
 * \param col1 コライダー1
 * \param col2 コライダー2
 */
void ResolveCollisionTable::SphereVsSphere(Collider* col1, Collider* col2)
{
	// 球のコライダーにキャスト
	Sphere* sphere1 = static_cast<Sphere*>(col1);
	Sphere* sphere2 = static_cast<Sphere*>(col2);

	// 衝突の解決
	Collision::ResolveCollision(sphere1, sphere2);
}

/**
 * \brief 球対メッシュの衝突解決
 * 
 * \param col1 コライダー1
 * \param col2 コライダー2
 */
void ResolveCollisionTable::SphereVsMesh(Collider* col1, Collider* col2)
{
	// 球のコライダーにキャスト
	Sphere* sphere = static_cast<Sphere*>(col1);
	// メッシュのコライダーにキャスト
	Mesh* mesh = static_cast<Mesh*>(col2);

	// 衝突の解決
	Collision::ResolveCollision(sphere, mesh);
}

void ResolveCollisionTable::MeshVsMesh(Collider* col1, Collider* col2)
{
	// 実装なし
}
