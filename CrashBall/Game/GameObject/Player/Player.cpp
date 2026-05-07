#include "pch.h"
#include "Player.h"
#include "Game/State/Player/PlayerMoveState.h"
#include <Game/State/Player/PlayerJumpState.h>

Player::Player(float radius)
	: Ball(radius)
	, m_stateMachine{ std::make_unique<StateMachine<Player>>() }
{

	auto collider = GetComponent<Sphere>();

	collider->SetOnCollisionStayCmd([this](Collider* other)
		{
			if (other->GetType() == ColliderType::Mesh)
			{
				SetIsGround(true);
			}
		});

	collider->SetOnCollisionExitCmd([this](Collider* other)
		{
			if (other->GetType() == ColliderType::Mesh)
			{
				SetIsGround(false);
			}
		});

	// ステートの生成
	m_stateMachine->CreateState<PlayerMoveState>();

	// ステートの生成
	m_stateMachine->CreateState<PlayerJumpState>();

	// 初期化
	m_stateMachine->Initialeze(this);

	// 初期のステートのセット
	m_stateMachine->ChangeState<PlayerJumpState>();
}

void Player::Update()
{
	m_stateMachine->Update();

	// 移動処理
	Move();

	// 回転処理
}
