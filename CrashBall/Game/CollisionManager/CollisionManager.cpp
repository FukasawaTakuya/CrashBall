#include "pch.h"
#include "CollisionManager.h"
#include "Collision.h"

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::Update()
{
	for (auto& obj1 : m_gameObjectList)
	{
		Collider* col1 = obj1->GetComponent<Collider>();
		auto layer = col1->GetLayerMask().layer;

		for (auto& obj2 : m_gameObjectList)
		{

			// 同一オブジェクトならリターン
			if (obj1 == obj2) continue;

			Collider* col2 = obj2->GetComponent<Collider>();
			auto mask = col2->GetLayerMask().mask;

			if (layer & mask)
			{
				col1->OnCollide(col2);
			}
		}
	}
}

