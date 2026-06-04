/*****************************************************************//**
 * \file   Player.cpp
 * \brief  プレイヤークラス
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#include "pch.h"
#include "Player.h"

 /**
 * \brief コンストラクタ
 * 
 * \param radius 半径
 */
Player::Player(float radius)
	: Ball(radius, ObjectTag::Player)
{
	m_playerStatusController = AddComponent<PlayerStatusController>();
	m_playerController = AddComponent<PlayerController>();
}

/**
 * \brief 初期化
 * 
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
	m_playerStatusController->Update();
	m_playerController->Update(gameContext);

	Ball::Update(gameContext);
}

/**
 * \brief 描画処理
 * 
 */
void Player::Render(const RenderContext& renderContext)
{
	Ball::Render(renderContext);
}

/**
 * \brief 終了処理
 * 
 */
void Player::Finalize()
{
}
