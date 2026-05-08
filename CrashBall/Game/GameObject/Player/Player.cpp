#include "pch.h"
#include "Player.h"
#include "Game/State/Player/PlayerMoveState.h"
#include "Game/State/Player/PlayerJumpState.h"

Player::Player(float radius)
	: Ball(radius)
	, m_stateMachine{ std::make_unique<StateMachine<Player>>() }
{
	// ステートの生成
	m_stateMachine->CreateState<PlayerMoveState>();

	// ステートの生成
	m_stateMachine->CreateState<PlayerJumpState>();

	// 初期化
	m_stateMachine->Initialeze(this);

	// 初期のステートのセット
	m_stateMachine->ChangeState<PlayerJumpState>();
}

void Player::Initialize(DirectX::SimpleMath::Vector3 position)
{
	Ball::Initialize(position);
}

void Player::Update()
{
	// ステートマシンの更新
	if (m_stateMachine != nullptr)
		m_stateMachine->Update();

	// 移動処理
	Ball::Move();
}

void Player::Draw()
{
	Ball::Draw();
}
