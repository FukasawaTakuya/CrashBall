#include "pch.h"
#include "Plane.h"

using namespace DirectX;

Plane::Plane()
{
}

/**
 * \brief 平面の設定
 * 
 * \param normal 法線
 * \param point 平面に含まれる座標
 */
void Plane::SetPlane(
	DirectX::SimpleMath::Vector3 normal,
	DirectX::SimpleMath::Vector3 point)
{
	m_vec4.x = normal.x;
	m_vec4.y = normal.y;
	m_vec4.z = normal.z;

	m_normal = normal;

	m_vec4.w = -(m_vec4.x * point.x + m_vec4.y * point.y + m_vec4.z * point.z);
}

/**
 * \brief 平面の設定
 * 
 * \param point1 平面に含まれる座標1
 * \param point2 平面に含まれる座標2
 * \param point3 平面に含まれる座標3
 */
void Plane::SetPlane(
	DirectX::SimpleMath::Vector3 point1,
	DirectX::SimpleMath::Vector3 point2,
	DirectX::SimpleMath::Vector3 point3)
{
	SimpleMath::Vector3 vec1 = point2 - point1;
	SimpleMath::Vector3 vec2 = point3 - point2;

	// 法線を求める
	SimpleMath::Vector3 normal = vec1.Cross(vec2);

	normal.Normalize();

	SetPlane(normal, point1);
}

void Plane::Rotate(DirectX::SimpleMath::Matrix rotate)
{
	// 平面情報の再定義
	DirectX::SimpleMath::Vector4 newVec4 = DirectX::XMPlaneTransform(m_vec4, rotate);
	// 平面情報の正規化
	m_vec4 = DirectX::XMPlaneNormalize(newVec4);
	// 法線ベクトルの回転
	m_normal = XMVector3Transform(m_normal, rotate);
}

/**
 * \brief ある点のと最短距離を求める
 * 
 * \param point
 * \return 
 */
float Plane::CalcLength(DirectX::SimpleMath::Vector3 point) const
{
	return std::abs(m_vec4.x * point.x + m_vec4.y * point.y + m_vec4.z * point.z + m_vec4.w);
}