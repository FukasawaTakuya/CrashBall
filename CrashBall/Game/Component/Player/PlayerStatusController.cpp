/*****************************************************************//**
 * \file   PlayerStatusController.cpp
 * \brief  プレイヤーステータス管理コンポーネント
 *
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#include "pch.h"
#include "PlayerStatusController.h"
#include "Game/Component/Default/Collider/Sphere.h"

RegisterComponent(PlayerStatusController)

/**
 * \brief コンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 */
PlayerStatusController::PlayerStatusController(IGameObject* gameObject)
	: Component(gameObject)
{
}

/**
 * \brief デストラクタ
 * 
 */
PlayerStatusController::~PlayerStatusController()
{
}

/**
 * \brief 更新
 * 
 */
void PlayerStatusController::Update(const GameContext& gameContext)
{
	if (m_floorMeshGetter == nullptr) return;

	// プレイヤーの面の数が攻撃コストより多ければフラグをオン
	if (m_floorMeshGetter->GetPlayerMeshCount() >= m_attackCost)
	{
		m_canAttack = true;
	}
	else
	{
		m_canAttack = false;
	}

	if (!m_isAttack)
	{
		int playerMeshCount = m_floorMeshGetter->GetPlayerMeshCount();
		int enemyMeshCount = m_floorMeshGetter->GetEnemyMeshCount();

		m_attackPower = playerMeshCount - enemyMeshCount;

		// 攻撃力を最低攻撃力以上に収める
		m_attackPower = std::max(m_attackPower, m_minAttackPower);
	}
}