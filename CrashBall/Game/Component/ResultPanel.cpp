#include "pch.h"
#include "ResultPanel.h"

#include "Game/Engine/Time.h"

RegisterComponent(ResultPanel)


void ResultPanel::Awake()
{
	m_backGround = GetGameObject()->GetComponent<SpriteRenderer>();
}

void ResultPanel::Start(const GameContext& gameContext)
{
	m_alpha = 0.0f;
	m_startResult = false;
}

void ResultPanel::Update(const GameContext& gameContext)
{
	if (m_startResult)
	{
		m_alpha += Time::GetUnscaleElapsedTime() * 1.5f;

		m_alpha = std::clamp(m_alpha, 0.0f, 1.0f);
	}

	m_backGround->SetAlpha(m_alpha);
	m_buttonText->SetColor({ 1.0f, 1.0f, 1.0f, 0.0f });
	m_resultText->SetColor({1.0f, 1.0f, 1.0f, 0.0f});
}
