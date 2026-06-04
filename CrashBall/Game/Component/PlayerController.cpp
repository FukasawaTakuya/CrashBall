#include "pch.h"
#include "PlayerController.h"

#include "Game/State/Player/PlayerMoveState.h"
#include "Game/State/Player/PlayerAttackState.h"
#include "EnemyController.h"

PlayerController::PlayerController(IGameObject* owner)
	: Component(owner)
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
				other->GetGameObject()->GetComponent<EnemyController>()
					->Damage(GetGameObject()->GetComponent<PlayerStatusController>()->GetAttackPower());
				m_stateMachine->ChangeState<PlayerMoveState>();
			}
		});
}

PlayerController::~PlayerController()
{
}

void PlayerController::Update(const GameContext& gameContext)
{
	// ステートマシンの更新
	if (m_stateMachine != nullptr)
		m_stateMachine->Update();
}
