/*****************************************************************//**
 * \file   TitleCamera.cpp
 * \brief  タイトルカメラ
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#include "pch.h"
#include "TitleCamera.h"
#include "Game/Component/Default/Physics/Transform.h"
#include "Game/Component/Camera/TargetCamera.h"

/**
 * \brief コンストラクタ
 * 
 */
TitleCamera::TitleCamera()
{
	// コンポーネントの追加
	AddComponent<Transform>();
	AddComponent<TargetCamera>(SimpleMath::Vector3(0.0f, 4.0f, 12.0f));
	m_cameraController = AddComponent<TitleCameraController>();
}

/**
 * \brief デストラクタ
 * 
 */
TitleCamera::~TitleCamera()
{
}

/**
 * \brief 初期化
 * 
 */
void TitleCamera::Initialize()
{
	m_cameraController->Initialize();
}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void TitleCamera::Update(const GameContext& gameContext)
{
	m_cameraController->Update();
}

/**
 * \brief 描画
 * 
 * \param renderContext 描画用のコンテキスト
 */
void TitleCamera::Render(const RenderContext& renderContext)
{
}

/**
 * \brief 終了処理
 * 
 */
void TitleCamera::Finalize()
{
}

void TitleCamera::SaveParam()
{
}

void TitleCamera::SaveInitParam()
{
}

void TitleCamera::ReloadJson()
{
}
