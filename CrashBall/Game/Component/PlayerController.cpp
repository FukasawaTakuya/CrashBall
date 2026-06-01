#include "pch.h"
#include "PlayerController.h"

#include "Game/State/Player/PlayerMoveState.h"
#include "Game/State/Player/PlayerAttackState.h"

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
		this
	};

	// ステートの生成
	m_stateMachine->CreateState<PlayerMoveState>(stateContext);
	m_stateMachine->CreateState<PlayerAttackState>(stateContext);

	// 初期のステートのセット
	m_stateMachine->ChangeState<PlayerMoveState>();

	GetGameObject()->GetComponent<Sphere>()->SetOnCollisionEnterCmd([this](Collider* other)
		{
			// 敵のコライダーと衝突した場合、移動ステートに遷移
			if (other->GetGameObject()->GetTag() == ObjectTag::Enemy &&
				m_stateMachine->GetCurrentStateType() == typeid(PlayerAttackState)) {
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
