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
	m_baseTypeid = typeid(TargetCameraController);
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
 * \brief 開始処理
 *
 * \param gameContext ゲーム用のコンテキスト
 */
void GameCameraController::Start(const GameContext& gameContext)
{
	TargetCameraController::Start(gameContext);
	TargetCameraController::TargetingTransform();
}

/**
 * \brief 更新
 *
 * \param gameContext ゲーム用のコンテキスト
 */
void GameCameraController::Update(const GameContext& gameContext)
{
	float elapsedTime = Time::GetElapsedTime();

	float stickValue = Input::GetInputState(InputAction::CameraRotateX).value;
	if (stickValue != 0.0f)
	{
		RotateX(XMConvertToRadians(m_rotateAngleRad * stickValue * elapsedTime));
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
	// 前方向ベクトル
	SimpleMath::Vector3 forward = m_camera->GetForward();

	// カメラの座標
	SimpleMath::Vector3 position = m_transform->GetWorldPosition();
	// 目的位置
	SimpleMath::Vector3 destination = m_targetTransform->GetWorldPosition() + m_offset * m_zoomRate;

	// 前方方向のみ補間
	SimpleMath::Vector3 posForward = forward * forward.Dot(position);
	SimpleMath::Vector3 desForward = forward * forward.Dot(destination);
	position = destination - desForward;
	posForward = SimpleMath::Vector3::Lerp(posForward, desForward, Time::GetUnscaleElapsedTime() * m_lerpSpeed);

	m_transform->SetWorldPosition(position + posForward);

	m_camera->LookAt(m_targetTransform->GetWorldPosition());
}
