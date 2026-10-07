/*****************************************************************//**
 * \file   PlayerStatusController.cpp
 * \brief  プレイヤーステータス管理コンポーネント
 *
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#include "pch.h"
#include "PlayerStatusController.h"

RegisterComponent(PlayerStatusController)

/**
 * \brief コンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 */
PlayerStatusController::PlayerStatusController(IGameObject* gameObject)
	: Component(gameObject)
{
	ModelRenderer* modelRenderer = GetGameObject()->GetComponent<ModelRenderer>();

	m_defaultAmbient = modelRenderer->GetAmbientColor();
}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void PlayerStatusController::Update(const GameContext& gameContext)
{
	if (m_pFloorMeshGetter == nullptr) return;

	// プレイヤーの面の数が攻撃コストより多ければフラグをオン
	if (m_pFloorMeshGetter->GetPlayerMeshCount() >= m_attackCost)
	{
		m_canAttack = true;
	}
	else
	{
		m_canAttack = false;
	}

	if (!m_goAttack)
	{
		int playerMeshCount = m_pFloorMeshGetter->GetPlayerMeshCount();
		int enemyMeshCount = m_pFloorMeshGetter->GetEnemyMeshCount();

		m_attackPower = (playerMeshCount - m_attackCost) / m_powerUpRate;

		// 攻撃力を最低攻撃力以上に収める
		m_attackPower = std::max(m_attackPower, m_minAttackPower);
	}
}