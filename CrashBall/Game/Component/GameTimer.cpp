#include "pch.h"
#include "GameTimer.h"

#include "Game/Engine/Time.h"

using namespace DirectX;

RegisterComponent(GameTimer)

void GameTimer::Awake()
{
	m_timeText = GetGameObject()->GetComponent<TextRenderer>();
}

/**
 * \brief 初期処理
 *
 * \param gameContext
 */
void GameTimer::Start(const GameContext& gameContext)
{
	m_timer = m_gameTime;
}

/**
 * \brief 更新
 * 
 * \param gameContext
 */
void GameTimer::Update(const GameContext& gameContext)
{
	m_timer -= Time::GetElapsedTime();

	m_timer = std::clamp(m_timer, 0.0f, m_gameTime);

	m_timeText->SetText(L"Time:{:.1f}", m_timer);
}
