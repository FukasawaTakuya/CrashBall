#include "pch.h"
#include "ChangeSceneScreen.h"
#include "Game/Engine/Time.h"
#include "Game/Engine/SceneManegement.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 * \param gameObject
 * \return 
 */
ChangeSceneScreen::ChangeSceneScreen(IGameObject* gameObject)
	: Component(gameObject)
{
}

/**
 * \brief アタッチ時の処理
 * 
 */
void ChangeSceneScreen::Awake()
{
	m_spriteRenderer = GetGameObject()->GetComponent<SpriteRenderer>();

	m_isIn = false;
	m_isOut = false;
}

/**
 * \brief 開始処理
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void ChangeSceneScreen::Start(const GameContext& gameContext)
{
}

