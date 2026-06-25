#include "pch.h"
#include "JsonDeserializers.h"

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
	j.at("spriteScale").get_to(spriteRenderer.m_spriteScale);
	j.at("layerDepth").get_to(spriteRenderer.m_layerDepth);
	j.at("fillOrigin").get_to(spriteRenderer.m_fillOrigin);
	j.at("spriteEffects").get_to(spriteRenderer.m_spriteEffects);
	j.at("spriteKey").get_to(spriteRenderer.m_spriteKey);
}

// ModelRendererへ変換
void from_json(const json& j, ModelRenderer& modelRenderer)
{
	j.at("modelKey").get_to(modelRenderer.m_modelKey);
}

// TextRendererへ変換
void from_json(const json& j, TextRenderer& textRenderer)
{
	j.at("text").get_to(textRenderer.m_text);
	j.at("color").get_to(textRenderer.m_color);
	j.at("fontScale").get_to(textRenderer.m_fontScale);
	j.at("layerDepth").get_to(textRenderer.m_layerDepth);
}

// Meshへ変換
void from_json(const json& j, Mesh& mesh)
{
	j.at("meshData").get_to(mesh.m_meshData);
}

// Sphereへ変換
void from_json(const json& j, Sphere& sphere)
{
	j.at("type").get_to(sphere.m_type);
	j.at("radius").get_to(sphere.m_radius);
}

// TargetCameraへ変換
void from_json(const json& j, TargetCamera& targetCamera)
{
	j.at("offset").get_to(targetCamera.m_offset);
}

// PlayerStatusControllerへ変換
void from_json(const json& j, PlayerStatusController& playerStatusController)
{
	j.at("attackCost").get_to(playerStatusController.m_ATTACK_COST);
	j.at("minAttackPower").get_to(playerStatusController.m_MIN_ATTACK_POWER);
}
