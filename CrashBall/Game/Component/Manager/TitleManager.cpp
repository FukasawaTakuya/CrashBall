/*****************************************************************//**
 * \file   TitleManager.h
 * \brief  タイトルマネージャ
 *
 * \author 深沢拓矢
 * \date   September 2026
 *********************************************************************/

#include "pch.h"
#include "TitleManager.h"

#include "Game/Engine/Input.h"
#include "Game/Engine/SceneManegement.h"

using namespace DirectX;

RegisterComponent(TitleManager);

/**
 * \brief コンストラクタ
 *
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 */
TitleManager::TitleManager(IGameObject* gameObject)
	: Component(gameObject)
{
}

/**
 * \brief 開始処理
 *
 * \param gameContext ゲーム用のコンテキスト
 */
void TitleManager::Start(const GameContext& gameContext)
{
	gameContext.soundManager->RegisterPlayBgmCommand("title");
	m_changeSceneScreen->SceneIn();
}

/**
 * \brief 更新
 *
 * \param gameContext ゲーム用のコンテキスト
 */
void TitleManager::Update(const GameContext& gameContext)
{
	if (Input::GetGamePadTracker()->a == GamePad::ButtonStateTracker::ButtonState::PRESSED || 
		Input::GetKeyTrigger(Keyboard::Space))
	{
		m_changeSceneScreen->SceneOut();
	}
}
