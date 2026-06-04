#include "pch.h"
#include "PlayerStatusController.h"

PlayerStatusController::PlayerStatusController(IGameObject* gameObject)
	: Component(gameObject)
{
}

PlayerStatusController::~PlayerStatusController()
{
}

void PlayerStatusController::Update()
{
	if (m_floorMeshGetter == nullptr) return;

	// プレイヤーの面の数が必須数より多ければフラグをオン
	if (m_floorMeshGetter->GetPlayerMeshCount() >= ATTACK_REQUIRED_FACE)
	{
		m_canAttack = true;
	}
	else
	{
		m_canAttack = false;
	}
}

/**
 * \brief 攻撃力を求める
 * 
 */
void PlayerStatusController::CalcAttackPower()
{
	int playerMeshCount = m_floorMeshGetter->GetPlayerMeshCount();
	int enemyMeshCount = m_floorMeshGetter->GetEnemyMeshCount();

	m_attackPower
		= (playerMeshCount - enemyMeshCount) * ATTACK_PER_FACE;

	// 攻撃力を範囲内に収める
	m_attackPower = std::clamp(m_attackPower, 0.0f, MAX_ATTACK_POWER);

}
