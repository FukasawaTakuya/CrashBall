/*****************************************************************//**
 * \file   FadeChageScreen.cpp
 * \brief  フェード遷移スクリーン
 *
 * \author 深沢拓矢
 * \date   September 2026
 *********************************************************************/

#include "pch.h"
#include "FadeChageScreen.h"

#include "Game/Engine/Time.h"
#include "Game/Engine/SceneManegement.h"

RegisterComponent(FadeChageScreen)

using namespace DirectX;

/**
 * \brief コンストラクタ
 *
 * \param gameObejct コンポーネントを所有するゲームオブジェクト
 * \return
 */
FadeChageScreen::FadeChageScreen(IGameObject* gameObejct)
	: ChangeSceneScreen(gameObejct)
{
	m_baseTypeid = typeid(ChangeSceneScreen);
}

/**
 * \brief アタッチ時の処理
 *
 */
void FadeChageScreen::Awake()
{
	ChangeSceneScreen::Awake();

	m_alpha.Initialize([](float start, float end, float t) { return std::lerp(start, end, t); });
}


/**
 * \brief 開始処理
 *
 * \param gameContext ゲーム用のコンテキスト
 */
void FadeChageScreen::Start(const GameContext& gameContext)
{
	ChangeSceneScreen::Start(gameContext);
}

/**
 * \brief 更新
 *
 * \param gameContext ゲーム用のコンテキスト
 */
void FadeChageScreen::Update(const GameContext& gameContext)
{
	m_alpha.DoEase(Time::GetUnscaleElapsedTime());

	m_spriteRenderer->SetAlpha(m_alpha.GetValue());

	if (!m_alpha.IsEase())
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
void FadeChageScreen::SceneIn()
{
	if (!m_isIn && !m_isOut)
	{
		m_isIn = true;
		m_alpha.Set(Ease::Linear, 1.0f, 0.0f, m_changeTime);
	}
}

/**
 * \brief シーンから出る
 * 
 */
void FadeChageScreen::SceneOut()
{
	if (!m_isIn && !m_isOut)
	{
		m_isOut = true;
		m_alpha.Set(Ease::Linear, 0.0f, 1.0f, m_changeTime);
	}
}
