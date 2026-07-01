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

using namespace DirectX;

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
 * \brief コンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 * \param other コピー元
 */
GameCameraController::GameCameraController(
	IGameObject* gameObject, 
	const GameCameraController& other)
	: Component(gameObject)
	, m_rotateAngleRad(other.m_rotateAngleRad)
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
	if (Input::GetKeyDown(Keyboard::Right)) {
		m_targetCamera->RotateX(XMConvertToRadians(m_rotateAngleRad) * elapsedTime);

	}
	else if (Input::GetKeyDown(Keyboard::Left)) {
		m_targetCamera->RotateX(-XMConvertToRadians(m_rotateAngleRad) * elapsedTime);
	}

	// ターゲットを追尾
	m_targetCamera->TargetingTransform();
}
