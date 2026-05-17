#pragma once

#include "Game/Component/Collider.h"
#include "Plane.h"

using namespace nlohmann;

/**
 * @brief 基底オブジェクト
 */
class Triangle
{
private:

	DirectX::SimpleMath::Vector3 m_point[3];

	DirectX::SimpleMath::Matrix m_rotate;

	Plane m_plane;

public:

	Triangle();
	Triangle(const Triangle& triangle, float scale = 1.0f);

public:

	DirectX::SimpleMath::Vector3* GetPoint() {
		return m_point;
	}

	Plane* GetPlane() { return &m_plane; }

	DirectX::SimpleMath::Vector3 GetCenter()
	{
		DirectX::SimpleMath::Vector3 center
		{
			(m_point[0].x + m_point[1].x + m_point[2].x) / 3,
			(m_point[0].y + m_point[1].y + m_point[2].y) / 3,
			(m_point[0].z + m_point[1].z + m_point[2].z) / 3,
		};

		return center;
	}

	void SetTriangle(
		DirectX::SimpleMath::Vector3 point1,
		DirectX::SimpleMath::Vector3 point2,
		DirectX::SimpleMath::Vector3 point3);

	void Rotate(DirectX::SimpleMath::Matrix rotate, DirectX::SimpleMath::Vector3 center);

public:
	friend void from_json(const json& j, Triangle& triangle);

};

inline void from_json(const json& j, Triangle& triangle) {
	j.at("point1").get_to(triangle.m_point[0]);
	j.at("point2").get_to(triangle.m_point[1]);
	j.at("point3").get_to(triangle.m_point[2]);
}

