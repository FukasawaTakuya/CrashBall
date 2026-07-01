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
#include "Game/Component/Camera/TargetCamera.h"



using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 */
GameCamera::GameCamera()
	: GameObject()
{
	// コンポーネントの追加
	AddComponent<Transform>();
	AddComponent<TargetCamera>(OFFSET);
	m_cameraController = AddComponent<GameCameraController>();
}

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
	AddComponent<TargetCamera>((*m_data)["targetCamera"].get<TargetCamera>());
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
void GameCamera::Initialize()
{
	m_cameraController->Initialize();
}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void GameCamera::Update(const GameContext& gameContext)
{
	m_cameraController->Update();
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
	(*m_data)["transform"] = *GetComponent<Transform>();
	(*m_data)["targetCamera"] = *GetComponent<TargetCamera>();
	(*m_data)["gameCameraController"] = *GetComponent<GameCameraController>();
}

/**
 * \brief 初期化時のパラメータの書き込み
 *
 */
void GameCamera::SaveInitParam()
{
}

/**
 * \brief パラメータの再読み込み
 *
 */
void GameCamera::ReloadParam()
{
	*GetComponent<Transform>() = (*m_data)["transform"];
	*GetComponent<TargetCamera>() = (*m_data)["targetCamera"];
	*GetComponent<GameCameraController>() = (*m_data)["gameCameraController"];

}

