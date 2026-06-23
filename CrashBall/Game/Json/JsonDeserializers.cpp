#include "pch.h"
#include "JsonDeserializers.h"

// Vector2へ変換
void DirectX::SimpleMath::from_json(const json& j, Vector2& vec2)
{
	j.at("x").get_to(vec2.x);
	j.at("y").get_to(vec2.y);
}

// Vector3へ変換
void DirectX::SimpleMath::from_json(const json& j, Vector3& vec3)
{
	j.at("x").get_to(vec3.x);
	j.at("y").get_to(vec3.y);
	j.at("z").get_to(vec3.z);
}

// Quaternionへ変換
void DirectX::SimpleMath::from_json(const json& j, Quaternion& q)
{
	Vector3 vec3 = j;

	q = Quaternion::CreateFromYawPitchRoll(vec3);
}

// Colorへ変換
void DirectX::SimpleMath::from_json(const json& j, Color& color)
{
	j.at("r").get_to(color.x);
	j.at("g").get_to(color.y);
	j.at("b").get_to(color.z);
	j.at("a").get_to(color.w);
}

// Traingleへ変換
void from_json(const json& j, Triangle& triangle)
{
	j.at("point1").get_to(triangle.m_point[0]);
	j.at("point2").get_to(triangle.m_point[1]);
	j.at("point3").get_to(triangle.m_point[2]);
}

// RectTransformへ変換
void from_json(const json& j, RectTransform& rectTransform)
{
	j.at("position").get_to(rectTransform.m_position);
	j.at("rotate").get_to(rectTransform.m_rotate);
	j.at("scele").get_to(rectTransform.m_rotate);
	j.at("origin").get_to(rectTransform.m_origin);
}

// Transformへ変換
void from_json(const json& j, Transform& transform)
{
	j.at("position").get_to(transform.m_position);
	j.at("rotate").get_to(transform.m_rotate);
	j.at("scale").get_to(transform.m_scale);
}

// Rigidbodyへ変換
void from_json(const json& j, Rigidbody& rigidbody)
{
	j.at("gravityAccelaration").get_to(rigidbody.m_gravityAcceleration);
	j.at("friction").get_to(rigidbody.m_friction);
	j.at("mass").get_to(rigidbody.m_mass);
	j.at("isDynamic").get_to(rigidbody.m_isDynamic);
}

// SpriteRendererへ変換
void from_json(const json& j, SpriteRenderer& spriteRenderer)
{
	j.at("color").get_to(spriteRenderer.m_color);
	j.at("width").get_to(spriteRenderer.m_width);
	j.at("height").get_to(spriteRenderer.m_height);
	j.at("spriteScale").get_to(spriteRenderer.m_spriteScale);
	j.at("layerDepth").get_to(spriteRenderer.m_layerDepth);
	j.at("fillOrigin").get_to(spriteRenderer.m_fillOrigin);
	j.at("spriteEffects").get_to(spriteRenderer.m_spriteEffects);
	j.at("spriteKey").get_to(spriteRenderer.m_spriteKey);
}
