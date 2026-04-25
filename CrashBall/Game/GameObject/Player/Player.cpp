#include "pch.h"
#include "Player.h"
#include "Game/State/Player/PlayerMoveState.h"

Player::Player(float radius)
	: Ball(radius)
	, m_stateMachine{ std::make_unique<StateMachine<Player>>() }
{
	m_stateMachine->SetOwner(this);

	m_stateMachine->CreateState<PlayerMoveState>();

	m_stateMachine->Initialeze(this);

	m_stateMachine->ChangeState<PlayerMoveState>();

}

void Player::Update()
{
	m_stateMachine->Update();

	Move();

	Rotate();
}
