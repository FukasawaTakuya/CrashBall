#include "pch.h"
#include "ButtonManager.h"

RegisterComponent(ButtonManager)

using namespace DirectX;

/**
 * \brief コンストラクタ
 *
 * \param gameObejct コンポーネントを所有するゲームオブジェクト
 * \return
 */
ButtonManager::ButtonManager(IGameObject* gameObejct)
	: Component(gameObejct)
{
}

/**
 * \brief アタッチ時の処理
 *
 */
void ButtonManager::Awake()
{
}

/**
 * \brief 開始処理
 *
 * \param gameContext ゲーム用のコンテキスト
 */
void ButtonManager::Start(const GameContext& gameContext)
{
}

/**
 * \brief 更新
 *
 * \param gameContext ゲーム用のコンテキスト
 */
void ButtonManager::Update(const GameContext& gameContext)
{
}
