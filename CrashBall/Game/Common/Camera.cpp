/*****************************************************************//**
 * \file   Camera.cpp
 * \brief  カメラに関するソースファイル
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#include "pch.h"
#include "Camera.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 */
Camera::Camera()
	: m_eye{}
	, m_target{}
	, m_up{ SimpleMath::Vector3::Up }
	, m_forward{}
	, m_projMat{}
	, m_viewMat{}
	, m_offset{}
	, m_zoomRate{}
{
}

/**
 * デストラクタ
 * 
 */
Camera::~Camera()
{
}

/**
 * \brief 初期化
 * 
 * \param projMat 射影行列
 */
void Camera::Initialize(const DirectX::SimpleMath::Matrix& projMat)
{
	m_projMat = projMat;
	m_offset = OFFSET;
	m_zoomRate = 1.0f;
}

/**
 * \brief X方向の回転.
 * 
 * \param angle
 */
void Camera::RotateX(float angle)
{
	if (m_offset == SimpleMath::Vector3::Zero) return;

	SimpleMath::Quaternion quaternion =
		SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::Down, angle);

	// オフセット
	m_offset = XMVector3Rotate(m_offset, quaternion);

	UpdataView();
}

/**
 * \brief Y方向の回転.
 *
 * \param angle
 */
void Camera::RotateY(float angle)
{
	if (m_offset == SimpleMath::Vector3::Zero) return;

	// 基準のベクトル
	SimpleMath::Vector3 baseVec{ m_forward.x, 0.0f, m_forward.z };

	// 現在の角度を求める
	float nowAngle = std::acos(m_forward.Dot(baseVec));

	// 角度が限界値より大きければreturn
	if (nowAngle + angle >= XMConvertToRadians(ROTATE_LIMIT) && m_offset.y > 0) return;
	else if (nowAngle - angle >= XMConvertToRadians(ROTATE_LIMIT) && m_offset.y < 0) return;

	// 右ベクトル
	m_right = XMVector3Cross(SimpleMath::Vector3::Up, m_forward);
	m_right.Normalize();

	// クオータニオンを求める
	SimpleMath::Quaternion quaternion =
		SimpleMath::Quaternion::CreateFromAxisAngle(m_right, angle);

	// オフセットの回転
	m_offset = XMVector3Rotate(m_offset, quaternion);

	UpdataView();
}

/**
 * \brief ズーム.
 * 
 * \param value
 */
void Camera::Zoom(float value)
{
	m_zoomRate += value;
}

/**
 * \brief カメラの追従.
 * 
 * \param pos
 */
void Camera::FollowCamera(DirectX::SimpleMath::Vector3 pos)
{
	SetEye(pos + m_offset * m_zoomRate);
	SetTarget(pos);
	UpdataView();
}

/**
 * \brief 視点の取得.
 * 
 * \return 視点
 */
DirectX::SimpleMath::Vector3 Camera::GetEye()
{
	return m_eye;
}

/**
 * \brief 注視点の取得.
 * 
 * \return 注視点
 */
DirectX::SimpleMath::Vector3 Camera::GetTarget()
{
	return m_target;
}

/**
 * \brief Rayの取得.
 * 
 * \param x	マウスのx座標
 * \param y	マウスのy座標
 * \return 
 */
DirectX::SimpleMath::Vector3 Camera::GetRay(float x, float y)
{
	SimpleMath::Vector3 nearPos
		= XMVector3Unproject(
			SimpleMath::Vector3{ x, y, 0.0f },
			0.0f, 0.0f,
			WIDTH, HEIGHT,
			0.0f, 1.0f,
			m_projMat, GetViewMat(), SimpleMath::Matrix::Identity);

	SimpleMath::Vector3 farPos
		= XMVector3Unproject(
			SimpleMath::Vector3{ x, y, 1.0f },
			0.0f, 0.0f,
			WIDTH, HEIGHT,
			0.0f, 1.0f,
			m_projMat, GetViewMat(), SimpleMath::Matrix::Identity);
	
	SimpleMath::Vector3 dire = farPos - nearPos;
	dire.Normalize();

	return dire;
}

/**
 * \brief ビュー行列の取得
 * 
 * \return ビュー行列
 */
DirectX::SimpleMath::Matrix Camera::GetViewMat()
{
	return m_viewMat;
}

/**
 * \brief 射影行列の取得
 * 
 * \return 射影行列
 */
DirectX::SimpleMath::Matrix Camera::GetProjMat()
{
	return m_projMat;
}

DirectX::SimpleMath::Vector3 Camera::GetForward()
{
	// 水平方向の前方ベクトル
	SimpleMath::Vector3 forward{ m_forward.x, 0.0f, m_forward.z };
	forward.Normalize();

	return forward;
}

DirectX::SimpleMath::Vector3 Camera::GetRight()
{
	// 水平方向の右ベクトル
	SimpleMath::Vector3 right{ m_right.x, 0.0f, m_right.z };
	right.Normalize();

	return right;
}

/**
 * \brief 注視点のセット.
 * 
 * \param target
 */
void Camera::SetTarget(DirectX::SimpleMath::Vector3 target)
{
	m_target = target;
	m_forward = XMVector3Normalize(m_target - m_eye);
}

/**
 * \brief 視点のセット.
 * 
 * \param eye
 */
void Camera::SetEye(DirectX::SimpleMath::Vector3 eye)
{
	m_eye = eye;
}

/**
 * \brief カメラのセット.
 * 
 * \param eye
 * \param target
 */
void Camera::SetCamera(
	const DirectX::SimpleMath::Vector3& eye, 
	const DirectX::SimpleMath::Vector3& target)
{
	SetEye(eye);
	SetTarget(target);

	m_viewMat = SimpleMath::Matrix::CreateLookAt(m_eye, (m_eye + m_forward), m_up);
}

/**
 * ビュー行列の更新.
 * 
 */
void Camera::UpdataView()
{
	// ターゲットを求める
	m_target = m_eye + m_forward;

	// 右ベクトル
	m_right = XMVector3Cross(m_forward, SimpleMath::Vector3::Up);
	m_right.Normalize();

	// 上ベクトルを求める
	m_up = XMVector3Cross(m_right, m_forward);
	m_up.Normalize();

	// ビュー行列を求める
	m_viewMat = SimpleMath::Matrix::CreateLookAt(m_eye, (m_eye + m_forward), m_up);
}
