/*****************************************************************//**
 * \file   CollisionManager.cpp
 * \brief  衝突管理クラス 
 * 
 * \author it252184
 * \date   May 2026
 *********************************************************************/

#include "pch.h"
#include "CollisionManager.h"
#include "Collision.h"

/**
 * \brief コンストラクタ
 * 
 */
CollisionManager::CollisionManager()
	: m_isCollsionTable			{ std::make_unique<IsCollisionTable>() }
	, m_resolveCollisionTable	{ std::make_unique<ResolveCollisionTable>() }
{
}

/**
 * \brief デストラクタ
 * 
 */
CollisionManager::~CollisionManager()
{
}

/**
 * \brief 更新
 * 
 */
void CollisionManager::Update()
{
	for (size_t i = 0; i < m_colliders.size() - 1; i++)
	{
		// レイヤーの取得
		auto layer = m_colliders[i]->GetLayerMask().layer;

		Collider* col1 = m_colliders[i];

		for (size_t j = i + 1; j < m_colliders.size(); j++)
		{
			Collider* col2 = m_colliders[j];

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

