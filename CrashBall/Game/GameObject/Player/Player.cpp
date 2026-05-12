/*****************************************************************//**
 * \file   Player.cpp
 * \brief  プレイヤークラスに関するソールファイル
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Player.h"
#include "Game/State/Player/PlayerMoveState.h"
#include "Game/State/Player/PlayerJumpState.h"
#include "Game/State/Player/PlayerAttackState.h"

// メンバ関数の定義 ===========================================================

/**
 * \brief コンストラクタ
 * 
 * \param radius 半径
 */
Player::Player(float radius)
	: Ball(radius)
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
void Player::Initialize(
	DirectX::SimpleMath::Vector3 position, 
	const Transform* enemyTransform)
{
	Ball::Initialize(position);
	m_enemyTransform = enemyTransform;
}

/**
 * \brief 更新処理
 * 
 */
void Player::Update()
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
void Player::Draw()
{
	Ball::Draw();
}
