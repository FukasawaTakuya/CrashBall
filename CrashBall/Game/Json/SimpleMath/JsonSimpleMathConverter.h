#pragma once
#include "SimpleMath.h"

namespace DirectX::SimpleMath
{
	// Vector2から変換
	void to_json(json& j, const Vector2& vec2);

	// Vector3から変換
	void to_json(json& j, const Vector3& vec3);

	// Quaternionから変換
	void to_json(json& j, const Quaternion& q);

	// Colorから変換
	void to_json(json& j, const Color& color);
}

namespace DirectX::SimpleMath
{
	// Vector2へ変換
	void from_json(const json& j, Vector2& vec2);

	// Vector3へ変換
	void from_json(const json& j, Vector3& vec3);

	// Quaternionへ変換
	void from_json(const json& j, Quaternion& q);

	// Colorへ変換
	void from_json(const json& j, Color& color);
}
