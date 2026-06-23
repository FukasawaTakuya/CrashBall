#pragma once

#include "nlohmann/json.hpp"
#include "Game/Geometory/Triangle.h"
#include "Game/Component/Default/Physics/RectTransform.h"
#include "Game/Component/Default/Physics/Transform.h"
#include "Game/Component/Default/Physics/Rigidbody.h"
#include "Game/Component/Default/Renderer/SpriteRenderer.h"
#include "Game/Component/Default/Renderer/ModelRenderer.h"
#include "Game/Component/Default/Renderer/TextRenderer.h"

using namespace nlohmann;

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

// Triangleへ変換
void from_json(const json& j, Triangle& triangle);

// RectTransformへ変換
void from_json(const json& j, RectTransform& rectTransform);

// Transformへ変換
void from_json(const json& j, Transform& transform);

// Rigidbodyへ変換
void from_json(const json& j, Rigidbody& rigidbody);

// SpriteRendererへ変換
void from_json(const json& j, SpriteRenderer& spriteRenderer);

// ModelRendererへ変換
void from_json(const json& j, ModelRenderer& modelRenderer);

// TextRendererへ変換
void from_json(const json& j, TextRenderer& textRenderer);
