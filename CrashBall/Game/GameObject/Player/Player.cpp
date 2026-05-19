/*****************************************************************//**
 * \file   Player.cpp
 * \brief  プレイヤークラス
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#include "pch.h"
#include "Player.h"
#include "Game/State/Player/PlayerMoveState.h"
#include "Game/State/Player/PlayerJumpState.h"
#include "Game/State/Player/PlayerAttackState.h"

/**
 * \brief コンストラクタ
 * 
 * \param radius 半径
 */
Player::Player(float radius)
	: Ball(radius, ObjectTag::Player)
	, m_stateMachine{ std::make_unique<StateMachine<Player>>() }
{
	// ステートの生成
	m_stateMachine->CreateState<PlayerMoveState>();
	m_stateMachine->CreateState<PlayerJumpState>();
	m_stateMachine->CreateState<PlayerAttackState>();

	// 初期化
	m_stateMachine->Initialeze(this);

	// 初期のステートのセット
	m_stateMachine->ChangeState<PlayerMoveState>();
}

/**
 * \brief 初期化
 * 
 * \param position 初期位置
 * \param enemyTransform 敵のトランスフォーム
 */
void Player::Initialize()
{
}

/**
 * \brief 更新処理
 * 
 */
void Player::Update(const GameContext& gameContext)
{
	// ステートマシンの更新
	if (m_stateMachine != nullptr)
		m_stateMachine->Update();

	// 移動処理
	Ball::Move();
}

/**
 * \brief 描画処理
 * 
 */
void Player::Render(const GameContext& gameContext)
{
	Ball::Render(gameContext);
}

/**
 * \brief 終了処理
 * 
 * \param gameContext
 */
void Player::Finalize()
{
}
