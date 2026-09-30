/*****************************************************************//**
 * \file   GameTimer.cpp
 * \brief  ゲームタイマー
 *
 * \author 深沢拓矢
 * \date   September 2026
 *********************************************************************/

#include "pch.h"
#include "GameTimer.h"

#include "Game/Engine/Time.h"

using namespace DirectX;

RegisterComponent(GameTimer)

/**
 * \brief コンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 */
GameTimer::GameTimer(IGameObject* gameObject)
	: Component(gameObject) 
{
}

/**
 * \brief アタッチ時の処理
 * 
 */
void GameTimer::Awake()
{
	m_timeText = GetGameObject()->GetComponent<TextRenderer>();
}

/**
 * \brief 開始処理
 *
 * \param gameContext ゲーム用のコンテキスト
 */
void GameTimer::Start(const GameContext& gameContext)
{
	m_timer = m_gameTime;
}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void GameTimer::Update(const GameContext& gameContext)
{
	m_timer -= Time::GetElapsedTime();

	m_timer = std::clamp(m_timer, 0.0f, m_gameTime);

	m_timeText->SetText(L"Time:{:.1f}", m_timer);
}
