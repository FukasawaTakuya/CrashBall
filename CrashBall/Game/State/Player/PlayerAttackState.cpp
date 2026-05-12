/*****************************************************************//**
 * \file   PlayerAttackState.cpp
 * \brief  プレイヤー攻撃ステートに関するソースファイル
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "PlayerAttackState.h"
#include "PlayerMoveState.h"
#include "Game/GameObject/Player/Player.h"
#include "Game/Common/TimeManager.h"

// メンバ関数の定義 ===================================================

/**
 * @brief コンストラクタ
 * 
 */
PlayerAttackState::PlayerAttackState()
	: m_timer{ 0.0f }
{
}

/**
 * @brief デストラクタ
 * 
 */
PlayerAttackState::~PlayerAttackState()
{
}

/**
 * \brief 初期化処理
 * 
 */
void PlayerAttackState::Initialize()
{
	// 衝突検知時の処理の設定
	m_owner->GetComponent<Sphere>()->SetOnCollisionEnterCmd([this](Collider* other) 
	{
		// 敵のコライダーと衝突した場合、移動ステートに遷移
		if (other->GetType() == ColliderType::Sphere) {
			m_pStateMachine->ChangeState<PlayerMoveState>();
		}
	});
}

/**
 * \brief 開始処理
 * 
 */
void PlayerAttackState::OnEnter()
{
	m_timer = 0.0f;
}

/**
 * \brief 更新処理
 * 
 */
void PlayerAttackState::Update()
{
	RigidBody* rigidbody = m_owner->GetComponent<RigidBody>();
	Transform* transform = m_owner->GetComponent<Transform>();

	SimpleMath::Vector3 attackDirection 
		= m_owner->GetEnemyTransform()->GetPosition() - transform->GetPosition();
	attackDirection.Normalize();

	rigidbody->SetVelocity(attackDirection * 30.0f);

	// タイマーの更新
	m_timer += TimeManager::Instance().GetElapsedTime();

	// 攻撃の持続時間を超えた場合、移動ステートに遷移
	if (m_timer >= ATTACK_DURATION) {
		m_pStateMachine->ChangeState<PlayerMoveState>();
	}
}

/**
 * \brief 終了処理
 */
void PlayerAttackState::OnExit()
{
}
