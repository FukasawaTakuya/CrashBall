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
					if (!col1->IsCollideObject(col2))
					{
						// Enter時処理
						col1->OnCollisionEnter(col2);
						col2->OnCollisionEnter(col1);
						// 衝突しているオブジェクトに追加
						col1->AddCollideObject(col2);
						col2->AddCollideObject(col1);
					}

					// 衝突中の処理
					col1->OnCollisionStay(col2);
					col2->OnCollisionStay(col1);

					// 衝突解決
					m_resolveCollisionTable->ResolveCollision(col1, col2);
				}
				else 
				{
					// 衝突状態ならExit処理
					if (col1->IsCollideObject(col2))
					{
						// Exit時処理
						col1->OnCollisionExit(col2);
						col2->OnCollisionExit(col1);
						// 衝突しているオブジェクトから削除
						col1->EraseCollideObject(col2);
						col2->EraseCollideObject(col1);
					}
				}
			}
		}
	}
}

