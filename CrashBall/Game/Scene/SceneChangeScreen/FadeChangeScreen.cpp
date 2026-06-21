#include "pch.h"
#include "FadeChangeScreen.h"

#include "Game/Common/Screen.h"
#include "Game/Engine/Time.h"

FadeChangeScreen::FadeChangeScreen()
	: GameObject()
{
	m_rectTransform = AddComponent<RectTransform>();
	m_spriteRenderer = AddComponent<SpriteRenderer>();

	m_spriteRenderer->SetLayerDepth(1.0f);
	m_rectTransform->SetPosition({ Screen::CENTER_X, Screen::CENTER_Y });
}

FadeChangeScreen::~FadeChangeScreen()
{
}

void FadeChangeScreen::Initialize()
{
}

void FadeChangeScreen::Update(const GameContext& gameContext)
{
	if (m_isFadeIn)
	{
		m_alpha -= Time::GetElapsedTime();

		if (m_alpha <= 0.0f)
		{
			m_alpha = 0.0f;
			m_isFadeIn = false;
			m_isFadeIn = true;
		}

		m_spriteRenderer->SetAlpha(m_alpha);
	}

	if (m_isFadeOut && !m_isFadeIn)
	{
		m_alpha += Time::GetElapsedTime();

		if (m_alpha >= 1.0f)
		{
			m_alpha = 1.0f;
			m_isFadeOut = false;
			m_isEndFadeOut = true;
		}

		m_spriteRenderer->SetAlpha(m_alpha);
	}

}

void FadeChangeScreen::Render(const RenderContext& renderContext)
{
	m_spriteRenderer->Render(renderContext.spriteRendererManager);
}

void FadeChangeScreen::Finalize()
{
}
