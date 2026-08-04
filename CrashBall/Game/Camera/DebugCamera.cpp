/*****************************************************************//**
 * \file   DebugCamera.cpp
 * \brief  デバッグカメラ
 *
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/


#include "pch.h"
#include "DebugCamera.h"

/**
 * \brief コンストラクタ
 * 
 */
DebugCamera::DebugCamera()
{
	AddComponent<Transform>();
	m_cameraController = AddComponent<DebugCameraController>();
}

/**
 * \brief デストラクタ
 * 
 */
DebugCamera::~DebugCamera()
{
}

/**
 * \brief 初期化
 * 
 */
void DebugCamera::Initialize()
{
	// TODO:GameObjectのStartに引数追加
	GameContext dummy;
	m_cameraController->Start(dummy);
}

/**
 * \brief 更新
 * 
 * \param gameContext
 */
void DebugCamera::Update(const GameContext& gameContext)
{
	m_cameraController->Update(gameContext);
}

/**
 * \brief 描画
 * 
 * \param renderContext 描画用のコンテキスト
 */
void DebugCamera::Render(const RenderContext& renderContext)
{
}

/**
 * \brief 終了処理
 * 
 */
void DebugCamera::Finalize()
{
}

/**
 * \brief パラメータの書き込み
 * 
 */
void DebugCamera::SaveParam()
{
}

/**
 * \brief パラメータの再読み込み
 * 
 */
void DebugCamera::ReloadParam()
{
}
