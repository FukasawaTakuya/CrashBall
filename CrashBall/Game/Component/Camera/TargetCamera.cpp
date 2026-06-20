/*****************************************************************//**
 * \file   TargetCamera.cpp
 * \brief  ターゲットカメラコンポーネント
 *
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#include "pch.h"
#include "TargetCamera.h"
#include "Game/Engine/Input.h"
#include "Game/Engine/Time.h"

/**
 * \brief コンストラクタ
 * 
 * \param gameObject
 */
TargetCamera::TargetCamera(IGameObject* gameObject)
	: Component(gameObject)
{
	m_transform = GetGameObject()->GetComponent<Transform>();
}

/**
 * \brief デストラクタ
 * 
 */
TargetCamera::~TargetCamera()
{
}

/**
 * \brief 初期化
 * 
 */
void TargetCamera::Initialize()
{
	m_zoomRate = 1.0f;
	m_offset = XMVector3Rotate(OFFSET, InitRotate);

	m_forward = XMVector3Rotate(SimpleMath::Vector3::Forward , InitRotate);
	m_right = XMVector3Rotate(SimpleMath::Vector3::Right, InitRotate);
	m_up = XMVector3Rotate(SimpleMath::Vector3::Up, InitRotate);

	//
	m_transform->SetQuaternion(InitRotate);
}

/**
 * \brief 更新
 * 
 */
void TargetCamera::Update()
{
	float elapsedTime = Time::GetElapsedTime();

	// 入力に応じて回転
	if (Input::GetKeyDown(Keyboard::Up)) {
		RotateY(XM_PIDIV4 * elapsedTime);
	}
	else if (Input::GetKeyDown(Keyboard::Down)) {
		RotateY(-XM_PIDIV4 * elapsedTime);
	}
	if (Input::GetKeyDown(Keyboard::Right)) {
		RotateX(XM_PIDIV4 * elapsedTime);
		
	}
	else if (Input::GetKeyDown(Keyboard::Left)) {
		RotateX(-XM_PIDIV4 * elapsedTime);
	}

	TargetingTransform();
}

/**
 * \brief X方向に回転
 * 
 * \param angleRad 回転角度
 */
void TargetCamera::RotateX(float angleRad)
{
	m_transform->Rotate(
		SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::Down, angleRad));

	// オフセットを回転
	m_offset = XMVector3Rotate(OFFSET, m_transform->GetQuaternion());

	// 各ベクトルを回転
	m_forward	= XMVector3Rotate(SimpleMath::Vector3::Forward, m_transform->GetQuaternion());
	m_right		= XMVector3Rotate(SimpleMath::Vector3::Right, m_transform->GetQuaternion());
	m_up		= XMVector3Rotate(SimpleMath::Vector3::Up, m_transform->GetQuaternion());

	m_isDirty = true;
}

/**
 * \brief Y方向に回転
 * 
 * \param angleRad 回転角度
 */
void TargetCamera::RotateY(float angleRad)
{
	m_transform->Rotate(
		SimpleMath::Quaternion::CreateFromAxisAngle(m_right, angleRad));

	// オフセットを回転
	m_offset = XMVector3Rotate(OFFSET, m_transform->GetQuaternion());

	// 各ベクトルを回転
	m_forward = XMVector3Rotate(SimpleMath::Vector3::Forward, m_transform->GetQuaternion());
	m_right = XMVector3Rotate(SimpleMath::Vector3::Right, m_transform->GetQuaternion());
	m_up = XMVector3Rotate(SimpleMath::Vector3::Up, m_transform->GetQuaternion());

	m_isDirty = true;
}

/**
 * \brief トランスフォームを追尾
 * 
 */
void TargetCamera::TargetingTransform()
{
	m_transform->SetPosition(m_targetTransform->GetPosition() + m_offset * m_zoomRate);

	m_isDirty = true;
}


/**
 * \brief ビュー行列の更新
 * 
 */
void TargetCamera::UpdateView() const
{
	m_view =
		SimpleMath::Matrix::CreateLookAt(m_transform->GetPosition(), m_transform->GetPosition() + m_forward, m_up);
}
