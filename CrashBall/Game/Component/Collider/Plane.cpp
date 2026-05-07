#include "pch.h"
#include "Plane.h"

Plane::Plane()
{
}

void Plane::SetPlane(
	DirectX::SimpleMath::Vector3 normal,
	DirectX::SimpleMath::Vector3 point)
{
	m_vec4.x = normal.x;
	m_vec4.y = normal.y;
	m_vec4.z = normal.z;
	m_point = point;

	m_vec4.w = -(m_vec4.x * m_point.x + m_vec4.y * m_point.y + m_vec4.z * m_point.z);
}

void Plane::SetPlane(
	DirectX::SimpleMath::Vector3 point1,
	DirectX::SimpleMath::Vector3 point2,
	DirectX::SimpleMath::Vector3 point3)
{
	SimpleMath::Vector3 vec1 = point2 - point1;
	SimpleMath::Vector3 vec2 = point3 - point2;

	SimpleMath::Vector3 normal = vec1.Cross(vec2);

	normal.Normalize();

	SetPlane(normal, point1);
}

void Plane::Rotate(DirectX::SimpleMath::Matrix rotate)
{
	// 平面情報の再定義
	DirectX::SimpleMath::Vector4 newVec = DirectX::XMPlaneTransform(m_vec4, rotate);
	// 平面情報の正規化
	m_vec4 = DirectX::XMPlaneNormalize(newVec);

}

float Plane::CalcLength(DirectX::SimpleMath::Vector3 point)
{
	return std::abs(m_vec4.x * point.x + m_vec4.y * point.y + m_vec4.z * point.z + m_vec4.w);
}

DirectX::SimpleMath::Vector3 Plane::GetNormal()
{
	// 法線ベクトル
	DirectX::SimpleMath::Vector3 normal;
	normal.x = m_vec4.x;
	normal.y = m_vec4.y;
	normal.z = m_vec4.z;

	normal.Normalize();

	return normal;
}

DirectX::SimpleMath::Vector3 Plane::GetSlope()
{
	// 重力の方向
	DirectX::SimpleMath::Vector3 v = DirectX::SimpleMath::Vector3::Down;
	// 法線ベクトル
	DirectX::SimpleMath::Vector3 normal = GetNormal();

	// 法線方向の成分
	float sub = v.Dot(normal);

	// 法線方向のベクトルを引く
	DirectX::SimpleMath::Vector3 slope = v - sub * normal;

	// 正規化
	slope.Normalize();

	return slope;
}
