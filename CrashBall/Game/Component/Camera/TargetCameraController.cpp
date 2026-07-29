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
	IGameObject* gameObject,
	const DirectX::SimpleMath::Vector3& offset)
	: Component(gameObject)
	, m_baseOffset(offset)
{
	// キャッシュの取得
	m_transform = GetGameObject()->GetComponent<Transform>();

	// オフセットからターゲット方向のベクトル
	SimpleMath::Vector3 offsetDire = XMVector3Normalize(-m_baseOffset);

	// オフセット分の回転
	m_offsetRotate = SimpleMath::Quaternion::FromToRotation(SimpleMath::Vector3::Forward, offsetDire);

	// 
	Initialize();
}

/**
 * \brief コピーコンストラクタ
 * 
 * \param gameObejct コンポーネントを所有するゲームオブジェクト
 * \param other ターゲットカメラコンポーネント
 */
TargetCameraController::TargetCameraController(
	IGameObject* gameObejct,
	const TargetCameraController& other)
	: Component(gameObejct)
	, m_baseOffset(other.m_baseOffset)
{
	// キャッシュの取得
	m_transform = GetGameObject()->GetComponent<Transform>();

	// オフセットからターゲット方向のベクトル
	SimpleMath::Vector3 offsetDire = XMVector3Normalize(-m_baseOffset);

	// オフセット分の回転
	m_offsetRotate = SimpleMath::Quaternion::FromToRotation(SimpleMath::Vector3::Forward, offsetDire);

	// 
	Initialize();
}

/**
 * \brief デストラクタ
 * 
 */
TargetCameraController::~TargetCameraController()
{
}

/**
 * \brief 初期化
 * 
 */
void TargetCameraController::Initialize()
{
	m_zoomRate = 1.0f;

	// 初期オフセットを設定
	m_offset = m_baseOffset;

	// 各ベクトルを回転
	m_forward	= XMVector3Rotate(SimpleMath::Vector3::Forward , m_offsetRotate);
	m_right		= XMVector3Rotate(SimpleMath::Vector3::Right, m_offsetRotate);
	m_up		= XMVector3Rotate(SimpleMath::Vector3::Up, m_offsetRotate);

	// 回転の設定
	m_transform->SetRotate(SimpleMath::Quaternion::Identity);
}

/**
 * \brief 更新
 * 
 */
void TargetCameraController::Update()
{
}

/**
 * \brief X方向に回転
 * 
 * \param angleRad 回転角度
 */
void TargetCameraController::RotateX(float angleRad)
{
	m_transform->Rotate(
		SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::Down, angleRad));

	// オフセットを回転
	m_offset = XMVector3Rotate(m_baseOffset, m_transform->GetWorldRotate());

	// 各ベクトルを回転
	m_forward = -XMVector3Normalize(m_offset);
	m_right = XMVector3Rotate(SimpleMath::Vector3::Right, m_offsetRotate * m_transform->GetWorldRotate());
	m_up = XMVector3Rotate(SimpleMath::Vector3::Up, m_offsetRotate * m_transform->GetWorldRotate());

	m_isDirty = true;
}

/**
 * \brief Y方向に回転
 * 
 * \param angleRad 回転角度
 */
void TargetCameraController::RotateY(float angleRad)
{
	m_transform->Rotate(
		SimpleMath::Quaternion::CreateFromAxisAngle(m_right, angleRad));

	// オフセットを回転
	m_offset = XMVector3Rotate(m_baseOffset, m_transform->GetWorldRotate());

	// 各ベクトルを回転
	m_forward = -XMVector3Normalize(m_offset);
	m_right = XMVector3Rotate(SimpleMath::Vector3::Right, m_offsetRotate * m_transform->GetWorldRotate());
	m_up = XMVector3Rotate(SimpleMath::Vector3::Up, m_offsetRotate * m_transform->GetWorldRotate());

	m_isDirty = true;
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

	m_transform->SetWorldPosition(position);

	m_isDirty = true;
}


/**
 * \brief ビュー行列の更新
 * 
 */
void TargetCameraController::UpdateView() const
{
	m_view =
		SimpleMath::Matrix::CreateLookAt(m_transform->GetWorldPosition(), m_transform->GetWorldPosition() + m_forward, m_up);
}
