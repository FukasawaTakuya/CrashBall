/*****************************************************************//**
 * \file   GameCameraController.cpp
 * \brief  ゲームカメラ操作コンポーネント
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#include "pch.h"
#include "GameCameraController.h"

#include "Game/Engine/Input.h"
#include "Game/Engine/Time.h"

/**
 * \brief コンストラクタ
 * 
 * \param gameObejct コンポーネントを所有するゲームオブジェクト
 */
GameCameraController::GameCameraController(IGameObject* gameObejct)
	: Component(gameObejct)
{
	// キャッシュの取得
	m_targetCamera = GetGameObject()->GetComponent<TargetCamera>();
}

/**
 * \brief デストラクタ
 * 
 */
GameCameraController::~GameCameraController()
{
}

/**
 * \brief 初期化
 * 
 */
void GameCameraController::Initialize()
{
	m_targetCamera->Initialize();
}

/**
 * \brief 更新
 * 
 */
void GameCameraController::Update()
{
	float elapsedTime = Time::GetElapsedTime();

	// 入力に応じて回転
	if (Input::GetKeyDown(Keyboard::Up)) {
		m_targetCamera->RotateY( ROTATE_ANGELRAD * elapsedTime);
	}
	else if (Input::GetKeyDown(Keyboard::Down)) {
		m_targetCamera->RotateY(-ROTATE_ANGELRAD * elapsedTime);
	}
	if (Input::GetKeyDown(Keyboard::Right)) {
		m_targetCamera->RotateX( ROTATE_ANGELRAD * elapsedTime);

	}
	else if (Input::GetKeyDown(Keyboard::Left)) {
		m_targetCamera->RotateX(-ROTATE_ANGELRAD * elapsedTime);
	}

	// ターゲットを追尾
	m_targetCamera->TargetingTransform();
}
