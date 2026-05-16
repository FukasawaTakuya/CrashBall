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

	m_normal = normal;

	m_vec4.w = -(m_vec4.x * point.x + m_vec4.y * point.y + m_vec4.z * point.z);
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
	// 法線ベクトルの回転
	m_normal = XMVector3Transform(m_normal, rotate);

}

float Plane::CalcLength(DirectX::SimpleMath::Vector3 point)
{
	return std::abs(m_vec4.x * point.x + m_vec4.y * point.y + m_vec4.z * point.z + m_vec4.w);
}