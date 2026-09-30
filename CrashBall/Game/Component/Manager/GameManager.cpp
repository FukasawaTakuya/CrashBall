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
}

/**
 * \brief 更新
 *
 * \param gameContext ゲーム用のコンテキスト
 */
void GameManager::Update(const GameContext& gameContext)
{
	if (Input::GetGamePadTracker()->start == GamePad::ButtonStateTracker::ButtonState::PRESSED)
	{
		m_changeSceneScreen->SceneOut();
	}

	if (m_pEnemyController->GetHp() <= 0.0f)
	{
		Time::GeratoTimeScale(-Time::GetUnscaleElapsedTime());

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
