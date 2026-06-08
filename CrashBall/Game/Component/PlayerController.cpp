/*****************************************************************//**
 * \file   PlayerController.cpp
 * \brief  プレイヤー操作コンポーネント
 *
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#include "pch.h"
#include "PlayerController.h"

#include "Game/State/Player/PlayerMoveState.h"
#include "Game/State/Player/PlayerAttackState.h"
#include "EnemyController.h"

/**
 * \brief コンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 */
PlayerController::PlayerController(IGameObject* gameObject)
	: Component(gameObject)
	, m_stateMachine{ std::make_unique<StateMachine<PlayerController>>(this) }
{
	// プレイヤーステート用のコンテキスト
	PlayerStateContext stateContext
	{
		GetGameObject()->GetComponent<RigidBody>(),
		GetGameObject()->GetComponent<Transform>(),
		GetGameObject()->GetComponent<BallController>(),
		GetGameObject()->GetComponent<PlayerStatusController>(),
		this
	};

	// ステートの生成
	m_stateMachine->CreateState<PlayerMoveState>(stateContext);
	m_stateMachine->CreateState<PlayerAttackState>(stateContext);

	// 初期のステートのセット
	m_stateMachine->ChangeState<PlayerMoveState>();

	// 衝突した瞬間の処理
	GetGameObject()->GetComponent<Sphere>()->SetOnCollisionEnterCmd([this](Collider* other)
		{
			// 敵のコライダーと衝突したとき攻撃ステートなら
			if (other->GetGameObject()->GetTag() == ObjectTag::Enemy &&
				m_stateMachine->GetCurrentStateType() == typeid(PlayerAttackState))
			{
				// ダメージ処理
				other->GetGameObject()->GetComponent<EnemyController>()
					->Damage(GetGameObject()->GetComponent<PlayerStatusController>()->GetAttackPower());
				// 移動ステートに遷移
				m_stateMachine->ChangeState<PlayerMoveState>();

			}
		});
}

/**
 * \brief デストラクタ
 * 
 */
PlayerController::~PlayerController()
{
}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void PlayerController::Update(const GameContext& gameContext)
{
	// ステートマシンの更新
	if (m_stateMachine != nullptr)
		m_stateMachine->Update();
}
