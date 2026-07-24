#include "pch.h"
#include "JsonSimpleMathConverter.h"

// Vector2から変換
void DirectX::SimpleMath::to_json(json& j, const Vector2& vec2)
{
	j = json{
		{ "x", vec2.x },
		{ "y", vec2.y }
	};
}

// Vector3から変換
void DirectX::SimpleMath::to_json(json& j, const Vector3& vec3)
{
	j = json{
		{ "x", vec3.x },
		{ "y", vec3.y },
		{ "z", vec3.z }
	};
}

// Quaternionから変換
void DirectX::SimpleMath::to_json(json& j, const Quaternion& q)
{
	Vector3 euler = q.ToEuler();

	j = euler;
}

// Colorから変換
void DirectX::SimpleMath::to_json(json& j, const Color& color)
{
	j = json{
		{ "r", color.R() },
		{ "g", color.G() },
		{ "b", color.B() },
		{ "a", color.A() }
	};
}

void DirectX::SimpleMath::to_json(ordered_json& j, const Vector2& vec2)
{
	j = json{
	{ "x", vec2.x },
	{ "y", vec2.y }
	};
}

void DirectX::SimpleMath::to_json(ordered_json& j, const Vector3& vec3)
{
	j = json{
	{ "x", vec3.x },
	{ "y", vec3.y },
	{ "z", vec3.z }
	};
}

void DirectX::SimpleMath::to_json(ordered_json& j, const Quaternion& q)
{
	Vector3 euler = q.ToEuler();

	j = euler;
}

void DirectX::SimpleMath::to_json(ordered_json& j, const Color& color)
{
	j = json{
	{ "r", color.R() },
	{ "g", color.G() },
	{ "b", color.B() },
	{ "a", color.A() }
	};
}

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

void DirectX::SimpleMath::from_json(const ordered_json& j, Vector2& vec2)
{
	j.at("x").get_to(vec2.x);
	j.at("y").get_to(vec2.y);
}

void DirectX::SimpleMath::from_json(const ordered_json& j, Vector3& vec3)
{
	j.at("x").get_to(vec3.x);
	j.at("y").get_to(vec3.y);
	j.at("z").get_to(vec3.z);
}

void DirectX::SimpleMath::from_json(const ordered_json& j, Quaternion& q)
{
	Vector3 vec3 = j;

	q = Quaternion::CreateFromYawPitchRoll(vec3);
}

void DirectX::SimpleMath::from_json(const ordered_json& j, Color& color)
{
	j.at("r").get_to(color.x);
	j.at("g").get_to(color.y);
	j.at("b").get_to(color.z);
	j.at("a").get_to(color.w);
}
