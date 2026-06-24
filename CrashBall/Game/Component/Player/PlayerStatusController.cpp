/*****************************************************************//**
 * \file   PlayerStatusController.cpp
 * \brief  プレイヤーステータス管理コンポーネント
 *
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#include "pch.h"
#include "PlayerStatusController.h"

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
void PlayerStatusController::Update()
{
	if (m_floorMeshGetter == nullptr) return;

	// プレイヤーの面の数が攻撃コストより多ければフラグをオン
	if (m_floorMeshGetter->GetPlayerMeshCount() >= ATTACK_COST)
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

		m_attackPower
			= (playerMeshCount - enemyMeshCount) * ATTACK_PER_FACE;

		// 攻撃力を範囲内に収める
		m_attackPower = std::max(m_attackPower, MIN_ATTACK_POWER);
	}
}