/*****************************************************************//**
 * \file   SlideChangeScreen.cpp
 * \brief  スライド遷移スクリーン
 *
 * \author 深沢拓矢
 * \date   September 2026
 *********************************************************************/

#include "pch.h"
#include "SlideChangeScreen.h"

#include "Game/Engine/Time.h"
#include "Game/Engine/SceneManegement.h"

RegisterComponent(SlideChangeScreen)

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 * \param gameObejct コンポーネントを所有するゲームオブジェクト
 * \return 
 */
SlideChangeScreen::SlideChangeScreen(IGameObject* gameObejct)
	: ChangeSceneScreen(gameObejct)
{
}

/**
 * \brief アタッチ時の処理
 * 
 */
void SlideChangeScreen::Awake()
{
	ChangeSceneScreen::Awake();
	m_fillAmount.Initialize([](float start, float end, float t) { return std::lerp(start, end, t); });
}

/**
 * \brief 開始処理
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void SlideChangeScreen::Start(const GameContext& gameContext)
{
	ChangeSceneScreen::Start(gameContext);
}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void SlideChangeScreen::Update(const GameContext& gameContext)
{
	m_fillAmount.DoEase(Time::GetUnscaleElapsedTime());

	m_spriteRenderer->SetFillAmount(m_fillAmount.GetValue());

	if (!m_fillAmount.IsEase())
	{
		if (m_isIn)
		{
			m_isIn = false;
		}
		else if (m_isOut)
		{
			m_isOut = false;
			SceneMamegement::RequestChangeScene(m_nextScene);
		}
	}
}

/**
 * \brief シーンに入る
 *
 */
void SlideChangeScreen::SceneIn()
{
	if (!m_isIn && !m_isOut)
	{
		m_isIn = true;
		m_fillAmount.Set(Ease::OutCubic, 1.0f, 0.0f, 0.5f);
	}
}

/**
 * \brief シーンから出る
 *
 */
void SlideChangeScreen::SceneOut()
{
	if (!m_isIn && !m_isOut)
	{
		m_isOut = true;
		m_fillAmount.Set(Ease::OutCubic, 0.0f, 1.0f, 0.5f);
	}
}
