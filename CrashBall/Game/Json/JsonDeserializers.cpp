#include "pch.h"
#include "JsonDeserializers.h"

void DirectX::SimpleMath::from_json(const json& j, Vector3& vec3)
{
	j.at("x").get_to(vec3.x);
	j.at("y").get_to(vec3.y);
	j.at("z").get_to(vec3.z);

}

void from_json(const json& j, Triangle& triangle)
{
	j.at("point1").get_to(triangle.m_point[0]);
	j.at("point2").get_to(triangle.m_point[1]);
	j.at("point3").get_to(triangle.m_point[2]);
}
