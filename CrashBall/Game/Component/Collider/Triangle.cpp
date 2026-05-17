#include "pch.h"
#include "Triangle.h"

Triangle::Triangle()
{
}

Triangle::Triangle(const Triangle& triangle, float scale)
	: m_point{ 
		triangle.m_point[0] * scale,
		triangle.m_point[1] * scale,
		triangle.m_point[2] * scale
	}
{
	m_plane.SetPlane(m_point[0], m_point[1], m_point[2]);
}
void Triangle::SetTriangle(
	DirectX::SimpleMath::Vector3 point1,
	DirectX::SimpleMath::Vector3 point2,
	DirectX::SimpleMath::Vector3 point3)
{
	m_point[0] = point1;
	m_point[1] = point2;
	m_point[2] = point3;

	m_plane.SetPlane(point1, point2, point3);
}

void Triangle::Rotate(
	DirectX::SimpleMath::Matrix rotate,
	DirectX::SimpleMath::Vector3 center)
{
	for (auto& point : m_point) {
		SimpleMath::Matrix trans
			= SimpleMath::Matrix::CreateTranslation(center);

		SimpleMath::Matrix invert = SimpleMath::Matrix::CreateTranslation(-center);

		SimpleMath::Matrix world = trans * rotate * invert;

		point = XMVector3Transform(point, world);
	}
	m_plane.Rotate(rotate);
}
