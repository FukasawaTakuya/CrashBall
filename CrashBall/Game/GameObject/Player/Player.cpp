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
Player::Player()
	: Ball(0.0f, ObjectTag::Player)
{
	// コンポーネントの追加
	m_playerStatusController = AddComponent<PlayerStatusController>();
	m_playerController = AddComponent<PlayerController>();
}

/**
 * \brief コンストラクタ
 * 
 * \param data Jsonデータ
 */
Player::Player(json* data)
	: Ball(data)
{
	// コンポーネントの追加
	m_playerStatusController = AddComponent<PlayerStatusController>((*data)["playerStatusController"]);
	m_playerController = AddComponent<PlayerController>((*m_data)["playerController"]);
}

/**
 * \brief 初期化
 * 
 */
void Player::Initialize()
{
	GetComponent<Transform>()->SetPosition((*m_data)["transform"]["position"]);

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

/**
 * \brief パラメータの書き込み
 * 
 */
void Player::SaveParam()
{
	(*m_data)["playerStatusController"] = *m_playerStatusController;
	(*m_data)["playerController"] = *m_playerController;

	Ball::SaveParam();
}

/**
 * \brief 初期化用のパラメータの書き込み
 * 
 */
void Player::SaveInitParam()
{
	(*m_data)["playerStatusController"] = *m_playerStatusController;

	Ball::SaveInitParam();
}

/**
 * \brief データの再読み込み
 * 
 */
void Player::ReloadJson()
{
	*m_playerStatusController = (*m_data)["playerStatusController"];
	*m_playerController = (*m_data)["playerController"];
	
	Ball::ReloadJson();
}
