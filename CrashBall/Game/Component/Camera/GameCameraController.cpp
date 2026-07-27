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
	, TargetCameraController(GetGameObject()->GetComponent<Transform>())
{
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
	, TargetCameraController(GetGameObject()->GetComponent<Transform>(), other.m_baseOffset)
	, m_rotateAngleRad(other.m_rotateAngleRad)
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
 * \brief 初期化
 * 
 */
void GameCameraController::Initialize()
{
	TargetCameraController::Initialize();
	TargetCameraController::TargetingTransform();
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
	SimpleMath::Vector3 position = m_transform->GetWorldPosition();
	SimpleMath::Vector3 destination = m_targetTransform->GetWorldPosition() + m_offset * m_zoomRate;

	// 前方方向のみ補間
	SimpleMath::Vector3 posForward = m_forward * m_forward.Dot(position);
	SimpleMath::Vector3 desForward = m_forward * m_forward.Dot(destination);
	position = destination - desForward;
	posForward = SimpleMath::Vector3::Lerp(posForward, desForward, Time::GetElapsedTime() * 7.0f);

	m_transform->SetWorldPosition(position + posForward);

	m_isDirty = true;

}
