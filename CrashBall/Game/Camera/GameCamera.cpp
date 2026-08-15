/*****************************************************************//**
 * \file   GameCamera.cpp
 * \brief  ゲームカメラ
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#include "pch.h"
#include "GameCamera.h"
#include "Game/Engine/Input.h"
#include "Game/Engine/Time.h"

#include "Game/Component/Default/Physics/Transform.h"
#include "Game/Component/Camera/TargetCameraController.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 * \param data データ
 */
GameCamera::GameCamera(json* data)
	: GameObject(data)
{
	// コンポーネントの追加
	AddComponent<Transform>((*m_data)["transform"]);
	m_cameraController = AddComponent<GameCameraController>((*m_data)["gameCameraController"]);
}

/**
 * デストラクタ
 *
 */
GameCamera::~GameCamera()
{
}

/**
 * \brief 初期化
 *
 */
void GameCamera::Start()
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
void GameCamera::Update(const GameContext& gameContext)
{
	m_cameraController->Update(gameContext);
}

/**
 * \brief 描画用のコンテキスト
 * 
 * \param renderContext
 */
void GameCamera::Render(const RenderContext& renderContext)
{
}

/**
 * \brief 終了処理
 * 
 */
void GameCamera::Finalize()
{
}

/**
 * \brief パラメータの書き込み
 * 
 */
void GameCamera::SaveParam()
{
	GameObject::SaveParam();

	(*m_data)["transform"] = *GetComponent<Transform>();
	(*m_data)["gameCameraController"] = *GetComponent<GameCameraController>();
}

/**
 * \brief パラメータの再読み込み
 *
 */
void GameCamera::ReloadParam()
{
	GameObject::ReloadParam();

	*GetComponent<Transform>() = (*m_data)["transform"];
	//*GetComponent<GameCameraController>() = (*m_data)["gameCameraController"];
}

