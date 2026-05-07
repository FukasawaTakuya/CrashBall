#include "pch.h"
#include "ResolveCollisionTable.h"

ResolveCollisionTable::ResolveCollisionTable()
{
	// 関数テーブルの登録
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

ResolveCollisionTable::~ResolveCollisionTable()
{
}

void ResolveCollisionTable::ResolveCollision(Collider* col1, Collider* col2)
{
	if (col1->GetType() > col2->GetType())
		std::swap(col1, col2);

	if (m_table[ToInt(col1->GetType())][ToInt(col2->GetType())] == nullptr)
	{
		return;
	}

	m_table[ToInt(col1->GetType())][ToInt(col2->GetType())](col1, col2);
}

void ResolveCollisionTable::SphereVsSphere(Collider* col1, Collider* col2)
{
	// 球のコライダーにキャスト
	Sphere* sphere1 = static_cast<Sphere*>(col1);
	Sphere* sphere2 = static_cast<Sphere*>(col2);

	//Collision::ResolveCollision(sphere1, sphere2);
}

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
