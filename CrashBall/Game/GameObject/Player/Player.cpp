#include "pch.h"
#include "Player.h"
#include "Game/State/Player/PlayerMoveState.h"

Player::Player(float radius)
	: Ball(radius)
	, m_stateMachine{ std::make_unique<StateMachine<Player>>() }
{
	// ステートの生成
	m_stateMachine->CreateState<PlayerMoveState>();

	// 初期化
	m_stateMachine->Initialeze(this);

	// 初期のステートのセット
	m_stateMachine->ChangeState<PlayerMoveState>();
}

void Player::Update()
{
	m_stateMachine->Update();

	// 移動処理
	Move();

	// 回転処理
}
