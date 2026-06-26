#pragma once

#include "Game/Json/Enum/JsonEnumSerializers.h"

#include "Game/Geometory/Triangle.h"
#include "Game/Component/Default/Physics/RectTransform.h"
#include "Game/Component/Default/Physics/Transform.h"
#include "Game/Component/Default/Physics/Rigidbody.h"
#include "Game/Component/Default/Renderer/SpriteRenderer.h"
#include "Game/Component/Default/Renderer/ModelRenderer.h"
#include "Game/Component/Default/Renderer/TextRenderer.h"
#include "Game/Component/Default/Collider/Mesh.h"
#include "Game/Component/Default/Collider/Sphere.h"
#include "Game/Component/Camera/TargetCamera.h"
#include "Game/Component/Player/PlayerStatusController.h"
#include "Game/Component/Player/PlayerController.h"

using namespace nlohmann;

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

// Meshへ変換
void from_json(const json& j, Mesh& mesh);

// Sphereへ変換
void from_json(const json& j, Sphere& sphere);

// TargetCameraへ変換
void from_json(const json& j, TargetCamera& targetCamera);

// PlayerControllerへ変換
void from_json(const json& j, PlayerController& playerController);

// PlayerStatusControllerへ変換
void from_json(const json& j, PlayerStatusController& playerStatusController);
