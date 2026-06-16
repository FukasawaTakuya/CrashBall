/*****************************************************************//**
 * \file   PlayerAttackState.cpp
 * \brief  プレイヤー攻撃ステート 
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#include "pch.h"
#include "PlayerAttackState.h"
#include "PlayerMoveState.h"
#include "Game/GameObject/Player/Player.h"
#include "Game/Component/EnemyController.h"
#include "Game/Engine/Time.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 */
PlayerAttackState::PlayerAttackState(const PlayerStateContext& stateContext)
	: PlayerStateBase(stateContext)
	, m_timer{ 0.0f }
{
	// 衝突した瞬間の処理
	m_stateContext.playerController->GetGameObject()->GetComponent<Sphere>()->SetOnCollisionEnterCmd([this](Collider* other)
		{
			// 敵のコライダーと衝突したとき攻撃ステートなら
			if (other->GetGameObject()->GetTag() == ObjectTag::Enemy)
			{
				// ダメージ処理
				other->GetGameObject()->GetComponent<EnemyController>()
					->Damage(m_stateContext.playerStatusController->GetAttackPower());
				// 移動ステートに遷移
				m_pStateMachine->ChangeState<PlayerMoveState>();
			}
		});
}

/**
 * \brief デストラクタ
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
	// 物理演算
	RigidBody* rigidbody = m_stateContext.rigitbody;
	// トランスフォーム
	Transform* transform = m_stateContext.transform;
	// プレイヤー操作
	PlayerController* playerController = m_stateContext.playerController;

	// 攻撃方向
	SimpleMath::Vector3 attackDirection 
		= playerController->GetEnemyTransform()->GetPosition() - transform->GetPosition();
	attackDirection.Normalize();

	rigidbody->SetVelocity(attackDirection * ATTACK_SPEED);

	// タイマーの更新
	m_timer += Time::GetElapsedTime();

	// 攻撃の持続時間を超えた場合、移動ステートに遷移
	if (m_timer >= ATTACK_DURATION) {
		m_pStateMachine->ChangeState<PlayerMoveState>();
		rigidbody->SetVelocity(SimpleMath::Vector3::Zero);
	}
}

/**
 * \brief 終了処理
 */
void PlayerAttackState::OnExit()
{
}
