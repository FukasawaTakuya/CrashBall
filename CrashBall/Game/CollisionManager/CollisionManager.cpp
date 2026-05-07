#include "pch.h"
#include "CollisionManager.h"
#include "Collision.h"

CollisionManager::CollisionManager()
	: m_isCollsionTable			{ std::make_unique<IsCollisionTable>() }
	, m_resolveCollisionTable	{ std::make_unique<ResolveCollisionTable>() }
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::Update()
{
	for (auto& col1 : m_colliderList)
	{
		// レイヤーの取得
		auto layer = col1->GetLayerMask().layer;

		for (auto& col2 : m_colliderList)
		{
			// 同一オブジェクトならスキップ
			if (col1 == col2) continue;

			auto mask = col2->GetLayerMask().mask;

			if (layer & mask)
			{
				if (m_isCollsionTable->IsCollision(col1, col2))
				{
					m_resolveCollisionTable->ResolveCollision(col1, col2);

					col1->OnCollisionStay(col2);
					col2->OnCollisionStay(col1);
				}
				else {
					col1->OnCollisionExit(col2);
					col2->OnCollisionExit(col1);
				}
			}
		}
	}
}

