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
#include "Game/Component/Camera/TargetCameraController.h"

/**
 * \brief コンストラクタ
 * 
 */
TitleCamera::TitleCamera()
{
	// コンポーネントの追加
	AddComponent<Transform>();
	m_cameraController = AddComponent<TitleCameraController>();
}

/**
 * \brief
 * 
 * \param data データ
 */
TitleCamera::TitleCamera(json* data)
	: GameObject(data)
{
	AddComponent<Transform>((*data)["transform"]);
	m_cameraController
		= AddComponent<TitleCameraController>((*m_data)["titleCameraController"]);

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
	// TODO:GameObjectのStartに引数追加
	GameContext dummy;
	m_cameraController->Start(dummy);
}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void TitleCamera::Update(const GameContext& gameContext)
{
	m_cameraController->Update(gameContext);
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

/**
 * \brief パラメータの書き込み
 * 
 */
void TitleCamera::SaveParam()
{
	GameObject::SaveParam();

	(*m_data)["transform"] = *GetComponent<Transform>();
	(*m_data)["titleCameraController"] = *GetComponent<TitleCameraController>();
}

/**
 * \brief パラメータの再読み込み
 * 
 */
void TitleCamera::ReloadParam()
{
	GameObject::ReloadParam();

	*GetComponent<Transform>() = (*m_data)["transform"];
	*GetComponent<TitleCameraController>() = (*m_data)["titleCameraController"];
}
