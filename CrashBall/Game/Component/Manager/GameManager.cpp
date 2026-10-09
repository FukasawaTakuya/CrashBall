/*****************************************************************//**
 * \file   GameManager.cpp
 * \brief  ゲームマネージャー
 *
 * \author 深沢拓矢
 * \date   September 2026
 *********************************************************************/

#include "pch.h"
#include "GameManager.h"

#include "Game/Engine/Input.h"
#include "Game/Engine/SceneManegement.h"
#include "Game/Engine/Time.h"

using namespace DirectX;

RegisterComponent(GameManager);

/**
 * \brief コンストラクタ
 *
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 */
GameManager::GameManager(IGameObject* gameObject)
	: Component(gameObject)
{
}

/**
 * \brief 開始処理
 *
 * \param gameContext ゲーム用のコンテキスト
 */
void GameManager::Start(const GameContext& gameContext)
{
	gameContext.soundManager->RegisterPlayBgmCommand("Game");
	m_changeSceneScreen->SceneIn();
	m_timeScale.Initialize([](float s, float e, float t) {return std::lerp(s, e, t); });
	m_timeScale.Set(Ease::Linear, 1.0f, 0.0f, 1.0f);
}

/**
 * \brief 更新
 *
 * \param gameContext ゲーム用のコンテキスト
 */
void GameManager::Update(const GameContext& gameContext)
{
	if (Input::GetGamePadTracker()->start == GamePad::ButtonStateTracker::ButtonState::PRESSED ||
		Input::GetKeyTrigger(Keyboard::Escape))
	{
		m_changeSceneScreen->SceneOut();
	}

	if (m_pEnemyController->GetHp() <= 0.0f)
	{
		m_timeScale.DoEase(Time::GetElapsedTime());
		Time::GenaratoTimeScale(-Time::GetUnscaleElapsedTime());
		//Time::SetTimeScale(m_timeScale.GetValue());

		if (Time::GetTimeScale() == 0.0f)
		{
			m_changeSceneScreen->SceneOut();
		}
	}

	if (m_pGameTimer->GetTimer() <= 0.0f)
	{
		m_changeSceneScreen->SceneOut();
	}
}
