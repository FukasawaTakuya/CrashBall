/*****************************************************************//**
 * \file   Player.cpp
 * \brief  プレイヤークラス
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#include "pch.h"
#include "Player.h"

#include "Game/Json/JsonDeserializers.h"
#include "Game/Json/JsonSerializers.h"

 /**
 * \brief コンストラクタ
 * 
 * \param radius 半径
 */
Player::Player()
	: Ball(RADIUS, ObjectTag::Player)
{
	// コンポーネントの追加
	m_playerStatusController = AddComponent<PlayerStatusController>();
	m_playerController = AddComponent<PlayerController>();

	// スケールの設定
	GetComponent<Transform>()->SetScale(SCALE);
}

Player::Player(json* data)
	: Ball(data)
{
	// コンポーネントの追加
	m_playerStatusController = AddComponent<PlayerStatusController>();
	m_playerController = AddComponent<PlayerController>();

	// スケールの設定
	//GetComponent<Transform>()->SetScale(SCALE);
}
\
/**
 * \brief 初期化
 * 
 */
void Player::Initialize()
{
	//m_playerController->Initialize();

	GetComponent<Transform>()->SetPosition(
		(*m_data)["transform"]["position"]
	);

	GetComponent<Rigidbody>()->SetVelocity(SimpleMath::Vector3::Zero);
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
