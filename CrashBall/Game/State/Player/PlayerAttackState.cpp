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
#include "Game/Component/Enemy/EnemyController.h"
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
	// 初期化
	m_hitStopTimer.Initialize([](float start, float end, float t) { return std::lerp(start, end, t); });

	// 衝突した瞬間の処理
	m_stateContext.playerController->GetGameObject()->GetComponent<Sphere>()->SetOnCollisionEnterCmd([this](Collider* other)
		{
			// 敵のコライダーと衝突したとき攻撃ステートなら
			if (other->GetGameObject()->GetTag() == ObjectTag::Enemy &&
				m_pStateMachine->GetCurrentStateType() == typeid(PlayerAttackState))
			{
				EnemyController* enemyController = other->GetGameObject()->GetComponent<EnemyController>();
				// ダメージ処理
				enemyController->Damage(m_stateContext.playerStatusController->GetAttackPower());
				// 攻撃フラグを設定
				m_stateContext.playerStatusController->SetIsAttack(false);
				// 効果音
				m_stateContext.gameContext->soundManager->RegisterPlaySeCommand("Crash");

				// 敵の体力が残っているならヒットストップ
				if (enemyController->GetHp() > 0)
				{
					// タイマーをセット
					m_hitStopTimer.Set(Ease::Linear, 0.0f, 0.05f, 0.05f);
					Time::SetTimeScale(0.0f);
				}
				else
				{
					// ステート遷移
					m_pStateMachine->ChangeState<PlayerMoveState>();
					// 移動速度を0にする
					m_stateContext.rigidbody->SetVelocity(SimpleMath::Vector3::Zero);
					// 攻撃フラグを設定
					m_stateContext.playerStatusController->SetIsAttack(false);
				}
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
 * \param gameContext ゲーム用のコンテキスト
 */
void PlayerAttackState::Update(const GameContext& gameContext)
{
	// 物理演算
	Rigidbody* rigidbody = m_stateContext.rigidbody;
	// トランスフォーム
	Transform* transform = m_stateContext.transform;
	// プレイヤー操作
	PlayerController* playerController = m_stateContext.playerController;

	// 攻撃方向
	SimpleMath::Vector3 attackDirection 
		= playerController->GetEnemyTransform()->GetWorldPosition() - transform->GetWorldPosition();
	attackDirection.Normalize();

	// 速度の設定
	rigidbody->SetVelocity(attackDirection * playerController->GetAttackSpeed());

	// タイマーの更新
	m_timer += Time::GetUnscaleElapsedTime();

	m_hitStopTimer.DoEase(Time::GetUnscaleElapsedTime());

	// 攻撃の持続時間を超えた場合、移動ステートに遷移
	if (m_timer >= playerController->GetAttackDuration() && !m_hitStopTimer.IsEase()) {
		// ステート遷移
		m_pStateMachine->ChangeState<PlayerMoveState>();
		// 移動速度を0にする
		rigidbody->SetVelocity(SimpleMath::Vector3::Zero);
		// 攻撃フラグを設定
		m_stateContext.playerStatusController->SetIsAttack(false);

		Time::SetTimeScale(1.0f);
	}
}

/**
 * \brief 終了処理
 */
void PlayerAttackState::OnExit()
{
}
