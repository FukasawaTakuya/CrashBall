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
TargetCamera::TargetCamera(
	IGameObject* gameObject,
	const DirectX::SimpleMath::Vector3& offset)
	: Component(gameObject)
{
	// キャッシュの取得
	m_transform = GetGameObject()->GetComponent<Transform>();

	// オフセットからターゲット方向のベクトル
	SimpleMath::Vector3 offsetDire = XMVector3Normalize(-offset);

	// 初期回転
	m_initRotate = SimpleMath::Quaternion::FromToRotation(SimpleMath::Vector3::Forward, offsetDire);

	// オフセットをForward方向に直す
	m_forwardOffset = XMVector3Rotate(offset, XMQuaternionInverse(m_initRotate));
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
	m_offset = XMVector3Rotate(m_forwardOffset, m_initRotate);

	m_forward	= XMVector3Rotate(SimpleMath::Vector3::Forward , m_initRotate);
	m_right		= XMVector3Rotate(SimpleMath::Vector3::Right, m_initRotate);
	m_up		= XMVector3Rotate(SimpleMath::Vector3::Up, m_initRotate);

	//
	m_transform->SetQuaternion(m_initRotate);
}

/**
 * \brief 更新
 * 
 */
void TargetCamera::Update()
{
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
	m_offset = XMVector3Rotate(m_forwardOffset, m_transform->GetRotate());

	// 各ベクトルを回転
	m_forward	= XMVector3Rotate(SimpleMath::Vector3::Forward, m_transform->GetRotate());
	m_right		= XMVector3Rotate(SimpleMath::Vector3::Right, m_transform->GetRotate());
	m_up		= XMVector3Rotate(SimpleMath::Vector3::Up, m_transform->GetRotate());

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
	m_offset = XMVector3Rotate(m_forwardOffset, m_transform->GetRotate());

	// 各ベクトルを回転
	m_forward = XMVector3Rotate(SimpleMath::Vector3::Forward, m_transform->GetRotate());
	m_right = XMVector3Rotate(SimpleMath::Vector3::Right, m_transform->GetRotate());
	m_up = XMVector3Rotate(SimpleMath::Vector3::Up, m_transform->GetRotate());

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
