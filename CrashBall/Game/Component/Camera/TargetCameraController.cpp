/*****************************************************************//**
 * \file   TargetCamera.cpp
 * \brief  ターゲットカメラコンポーネント
 *
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#include "pch.h"
#include "TargetCameraController.h"
#include "Game/Engine/Time.h"

using namespace DirectX;
RegisterComponent(TargetCameraController)

/**
 * \brief コンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 */
TargetCameraController::TargetCameraController(
	IGameObject* gameObject)
	: Component(gameObject)
{
}


/**
 * \brief アタッチ時の処理
 * 
 */
void TargetCameraController::Awake()
{
	// キャッシュの取得
	m_transform = GetGameObject()->GetComponent<Transform>();
	m_camera = GetGameObject()->GetComponent<Camera>();

	m_offsetRotate = SimpleMath::Quaternion::Identity;
}

/**
 * \brief 開始処理
 *
 * \param gameContext ゲーム用のコンテキスト
 */
void TargetCameraController::Start(const GameContext& gameContext)
{
	m_offsetRotate = SimpleMath::Quaternion::Identity;
	m_offset = m_baseOffset;
	TargetingTransform();
	m_camera->LookAt(m_targetTransform->GetWorldPosition());
}

/**
 * \brief 更新
 *
 * \param gameContext ゲーム用のコンテキスト
 */
void TargetCameraController::Update(const GameContext& gameContext)
{
}

/**
 * \brief X方向に回転
 * 
 * \param angleRad 回転角度
 */
void TargetCameraController::RotateX(float angleRad)
{
	m_offsetRotate
		*= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::Down, angleRad);
		
	m_offset = XMVector3Rotate(m_baseOffset, m_offsetRotate);
}

/**
 * \brief Y方向に回転
 * 
 * \param angleRad 回転角度
 */
void TargetCameraController::RotateY(float angleRad)
{
	m_offsetRotate
		*= SimpleMath::Quaternion::CreateFromAxisAngle(m_camera->GetHorizontalRight(), angleRad);

	m_offset = XMVector3Rotate(m_baseOffset, m_offsetRotate);
}

/**
 * \brief オフセットのズーム
 * 
 * \param value 
 */
void TargetCameraController::Zoom(float value)
{
	m_zoomRate += value;
}

/**
 * \brief トランスフォームを追尾
 * 
 */
void TargetCameraController::TargetingTransform()
{
	SimpleMath::Vector3 position = m_targetTransform->GetWorldPosition() + m_offset * m_zoomRate;

	m_camera->LookAt(m_targetTransform->GetWorldPosition());

	m_transform->SetWorldPosition(position);
}

