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
#include "Game/Component/TargetCamera.h"



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
	AddComponent<TargetCamera>();
	m_cameraController = AddComponent<GameCameraController>();
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

