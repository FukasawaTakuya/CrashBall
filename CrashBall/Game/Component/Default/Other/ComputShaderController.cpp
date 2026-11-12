#include "pch.h"
#include "ComputShaderController.h"

RegisterComponent(ComputShaderController)

using namespace DirectX;

/**
 * \brief コンストラクタ
 *
 * \param gameObejct コンポーネントを所有するゲームオブジェクト
 * \return
 */
ComputShaderController::ComputShaderController(IGameObject* gameObejct)
	: Component(gameObejct)
{
}

/**
 * \brief アタッチ時の処理
 *
 */
void ComputShaderController::Awake()
{
}

/**
 * \brief 開始処理
 *
 * \param gameContext ゲーム用のコンテキスト
 */
void ComputShaderController::Start(const GameContext& gameContext)
{
}

/**
 * \brief 更新
 *
 * \param gameContext ゲーム用のコンテキスト
 */
void ComputShaderController::Update(const GameContext& gameContext)
{
	gameContext.computShaderDispathcer->RegisterDispatchCommand(
		m_computShader.get(),
		m_groupNum);
}
