/*****************************************************************//**
 * \file   FadeChangeScreen.h
 * \brief  フェードシーン遷移演出
 *
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/


#include "pch.h"
#include "FadeChangeScreen.h"

#include "Game/Common/Screen.h"
#include "Game/Engine/Time.h"

/**
 * \brief コンストラクタ
 * 
 */
FadeChangeScreen::FadeChangeScreen()
{
	m_rectTransform = AddComponent<RectTransform>();
	m_spriteRenderer = AddComponent<SpriteRenderer>();

	// 描画順の設定
	m_spriteRenderer->SetLayerDepth(1.0f);
	// 描画位置の設定
	m_rectTransform->SetPosition({ Screen::CENTER_X, Screen::CENTER_Y });
}

/**
 * \brief デストラクタ
 * 
 */
FadeChangeScreen::~FadeChangeScreen()
{
}

/**
 * \brief 初期化
 * 
 */
void FadeChangeScreen::Initialize()
{
}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void FadeChangeScreen::Update(const GameContext& gameContext)
{
	// フェードイン処理
	if (m_isFadeIn)
	{
		m_alpha -= Time::GetElapsedTime();

		if (m_alpha <= 0.0f)
		{
			m_alpha = 0.0f;
			m_isFadeIn = false;
		}

		m_spriteRenderer->SetAlpha(m_alpha);
	}

	// フェードアウト処理
	if (m_isFadeOut && !m_isFadeIn)
	{
		m_alpha += Time::GetElapsedTime();

		if (m_alpha >= 1.0f)
		{
			m_alpha = 1.0f;
			m_isFadeOut = false;
		}

		m_spriteRenderer->SetAlpha(m_alpha);
	}

}

/**
 * \brief 描画
 * 
 * \param renderContext 描画用のコンテキスト
 */
void FadeChangeScreen::Render(const RenderContext& renderContext)
{
	m_spriteRenderer->Render(renderContext.spriteRendererManager);
}

/**
 * \brief 終了処理
 * 
 */
void FadeChangeScreen::Finalize()
{
}
