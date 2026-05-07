#include "pch.h"
#include "IsCollisionTable.h"

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

IsCollisionTable::~IsCollisionTable()
{
}

bool IsCollisionTable::IsCollision(Collider* col1, Collider* col2)
{
	if(col1->GetType() > col2->GetType())
		std::swap(col1, col2);

	if (m_isCollisionTable[ToInt(col1->GetType())][ToInt(col2->GetType())] == nullptr)
	{
		return false;
	}

	return m_isCollisionTable[ToInt(col1->GetType())]
		[ToInt(col2->GetType())](col1, col2);
}

bool IsCollisionTable::SphereVsSphere(Collider* col1, Collider* col2)
{
	// 球のコライダーにキャスト
	Sphere* sphere1 = static_cast<Sphere*>(col1);
	Sphere* sphere2 = static_cast<Sphere*>(col2);

	return Collision::IsCollision(sphere1, sphere2);
}

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
