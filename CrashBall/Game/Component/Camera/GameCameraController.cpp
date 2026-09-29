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
RegisterComponent(GameCameraController)

/**
 * \brief コンストラクタ
 * 
 * \param gameObejct コンポーネントを所有するゲームオブジェクト
 */
GameCameraController::GameCameraController(IGameObject* gameObejct)
	: TargetCameraController(gameObejct)
{
}

/**
 * \brief デストラクタ
 * 
 */
GameCameraController::~GameCameraController()
{
}

/**
 * \brief アタッチ時の処理
 * 
 */
void GameCameraController::Awake()
{
	TargetCameraController::Awake();

	// キャッシュの取得
	m_targetCamera = GetGameObject()->GetComponent<TargetCameraController>();
}

/**
 * \brief 初期化
 * 
 */
void GameCameraController::Start(const GameContext& gameContext)
{
	TargetCameraController::Start(gameContext);
	TargetCameraController::TargetingTransform();
}

/**
 * \brief 更新
 * 
 */
void GameCameraController::Update(const GameContext& gameContext)
{
	float elapsedTime = Time::GetElapsedTime();

	float stickValue = Input::GetGamePad().thumbSticks.rightX;
	if (stickValue != 0.0f)
	{
		RotateX(XMConvertToRadians(m_rotateAngleRad * stickValue * elapsedTime));
	}


	// 入力に応じて回転
	if (Input::GetKeyDown(Keyboard::Right)) {
		RotateX(XMConvertToRadians(m_rotateAngleRad) * elapsedTime);

	}
	else if (Input::GetKeyDown(Keyboard::Left)) {
		RotateX(-XMConvertToRadians(m_rotateAngleRad) * elapsedTime);
	}
	// ターゲットを追尾
	TargetingTransform();
}

/**
 * \brief トランスフォームを追尾
 * 
 */
void GameCameraController::TargetingTransform()
{
	SimpleMath::Vector3 forward = m_camera->GetForward();

	SimpleMath::Vector3 position = m_transform->GetWorldPosition();
	SimpleMath::Vector3 destination = m_targetTransform->GetWorldPosition() + m_offset * m_zoomRate;

	// 前方方向のみ補間
	SimpleMath::Vector3 posForward = forward * forward.Dot(position);
	SimpleMath::Vector3 desForward = forward * forward.Dot(destination);
	position = destination - desForward;
	posForward = SimpleMath::Vector3::Lerp(posForward, desForward, Time::GetElapsedTime() * 7.0f);

	m_transform->SetWorldPosition(position + posForward);

	m_camera->LookAt(m_targetTransform->GetWorldPosition());
}
