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
	// BGMの登録
	gameContext.soundManager->RegisterPlayBgmCommand("Game");
	// スクリーン開始
	m_changeSceneScreen->SceneIn();
	// イージングの初期化
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
	if (Input::GetInputState(InputAction::Exit).isTrigger)
	{
		m_changeSceneScreen->SceneOut("TitleScene");
	}

	// 敵の体力がなくなった時
	if (m_pEnemyController->GetHp() <= 0.0f)
	{
		m_timeScale.DoEase(Time::GetElapsedTime());
		Time::GenaratoTimeScale(-Time::GetUnscaleElapsedTime());

		if (Time::GetTimeScale() == 0.0f)
		{
			m_changeSceneScreen->SceneOut("TitleScene");
		}
	}

	// タイマーが０になった時
	if (m_pGameTimer->GetTimer() == 0.0f)
	{
		m_changeSceneScreen->SceneOut("TitleScene");
	}
}
