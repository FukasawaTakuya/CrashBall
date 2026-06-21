/*****************************************************************//**
 * \file   IsCollisionTable.cpp
 * \brief  衝突検知関数テーブル 
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#include "pch.h"
#include "IsCollisionTable.h"

/**
 * \brief コンストラクタ
 * 
 */
IsCollisionTable::IsCollisionTable()
{
	// 関数テーブルの登録
	m_isCollisionTable[ToInt(ColliderType::Sphere)]
		[ToInt(ColliderType::Sphere)]
		= SphereVsSphere;

	m_isCollisionTable[ToInt(ColliderType::Sphere)]
		[ToInt(ColliderType::Mesh)]
		= SphereVsMesh;

	m_isCollisionTable[ToInt(ColliderType::Mesh)]
		[ToInt(ColliderType::Sphere)]
		= SphereVsMesh;

	//m_isCollisionTable[ToInt(ColliderType::Mesh)]
	//	[ToInt(ColliderType::Mesh)]
	//	= MeshVsMesh;
}

/**
 * \brief デストラクタ
 * 
 */
IsCollisionTable::~IsCollisionTable()
{
}

/**
 * \brief 衝突判定
 * 
 * \param col1 コライダー1
 * \param col2 コライダー2
 * \return 衝突しているかどうか
 */
bool IsCollisionTable::IsCollision(Collider* col1, Collider* col2)
{
	// コライダーのタイプが大きい方をcol2にする
	if(col1->GetType() > col2->GetType())
		std::swap(col1, col2);

	// 関数テーブルに登録されていない組み合わせならリターン
	if (m_isCollisionTable[ToInt(col1->GetType())][ToInt(col2->GetType())] == nullptr)
	{
		return false;
	}

	// 関数テーブルから関数を呼び出す
	return m_isCollisionTable[ToInt(col1->GetType())][ToInt(col2->GetType())](col1, col2);
}

/**
 * \brief 球対球の衝突判定
 * 
 * \param col1 コライダー1
 * \param col2 コライダー2
 * \return 衝突しているかどうか
 */
bool IsCollisionTable::SphereVsSphere(Collider* col1, Collider* col2)
{
	// 球のコライダーにキャスト
	Sphere* sphere1 = static_cast<Sphere*>(col1);
	Sphere* sphere2 = static_cast<Sphere*>(col2);

	return Collision::IsCollision(sphere1, sphere2);
}

/**
 * \brief 球対メッシュの衝突判定
 * 
 * \param col1 コライダー1
 * \param col2 コライダー2
 * \return 衝突しているかどうか
 */
bool IsCollisionTable::SphereVsMesh(Collider* col1, Collider* col2)
{
	// 球のコライダーにキャスト
	Sphere* sphere = static_cast<Sphere*>(col1);
	// メッシュのコライダーにキャスト
	Mesh* mesh = static_cast<Mesh*>(col2);

	return Collision::IsCollision(sphere, mesh);
}

bool IsCollisionTable::MeshVsMesh(Collider* col1, Collider* col2)
{
	// 実装なし
	return false;
}
