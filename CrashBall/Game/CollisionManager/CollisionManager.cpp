/*****************************************************************//**
 * \file   CollisionManager.cpp
 * \brief  衝突管理クラスに関するソースファイル
 * 
 * \author it252184
 * \date   May 2026
 *********************************************************************/

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

			// マスクの取得
			auto mask = col2->GetLayerMask().mask;

			if (layer & mask)
			{
				if (m_isCollsionTable->IsCollision(col1, col2))
				{
					// 衝突状態でなければEnter処理
					if (!col1->GetIsCollide())
					{
						col1->OnCollisionEnter(col2);
					}
					if (!col2->GetIsCollide())
					{
						col2->OnCollisionEnter(col1);
					}

					// 衝突中の処理
					col1->OnCollisionStay(col2);
					col2->OnCollisionStay(col1);

					// 衝突解決
					m_resolveCollisionTable->ResolveCollision(col1, col2);
				}
				else {
					// TODO:ちゃんと離れた時の判定を行う
					col1->OnCollisionExit(col2);
					col2->OnCollisionExit(col1);
				}
			}
		}
	}
}

