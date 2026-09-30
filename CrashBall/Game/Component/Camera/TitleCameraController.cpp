/*****************************************************************//**
 * \file   TitleCameraController.h
 * \brief  タイトルカメラ操作コンポーネント
 *
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/


#include "pch.h"
#include "TitleCameraController.h"

#include "Game/Engine/Time.h"

using namespace DirectX;
RegisterComponent(TitleCameraController)

/**
 * \brief コンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 */
TitleCameraController::TitleCameraController(IGameObject* gameObject)
	: TargetCameraController(gameObject)
{
}

/**
 * \brief アタッチ時の処理
 * 
 */
void TitleCameraController::Awake()
{
	TargetCameraController::Awake();
}

/**
 * \brief 開始処理
 *
 * \param gameContext ゲーム用のコンテキスト
 */
void TitleCameraController::Start(const GameContext& gameContext)
{
	TargetCameraController::Start(gameContext);
}

/**
 * \brief 更新
 *
 * \param gameContext ゲーム用のコンテキスト
 */
void TitleCameraController::Update(const GameContext& gameContext)
{
	RotateX(XMConvertToRadians(m_rotateAngeleRad) * Time::GetElapsedTime());

	TargetingTransform();
}
