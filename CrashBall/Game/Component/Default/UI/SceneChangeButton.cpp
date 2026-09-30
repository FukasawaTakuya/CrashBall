/*****************************************************************//**
 * \file   SceneChangeButton.h
 * \brief  シーン変更ボタン
 *
 * \author 深沢拓矢
 * \date   September 2026
 *********************************************************************/

#include "pch.h"
#include "SceneChangeButton.h"

#include "Game/Engine/SceneManegement.h"

RegisterComponent(SceneChangeButton)

/**
 * \brief コンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 */
SceneChangeButton::SceneChangeButton(IGameObject* gameObject)
	: ButtonController(gameObject)
{
	m_baseTypeid = typeid(ButtonController);
}

/**
 * \brief アタッチ時の処理
 * 
 */
void SceneChangeButton::Awake()
{
	ButtonController::Awake();

	SetOnPushCommand([&]()
		{
			SceneMamegement::RequestChangeScene(m_nextSceneName);
		});
}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void SceneChangeButton::Update(const GameContext& gameContext)
{
	ButtonController::Update(gameContext);
}
