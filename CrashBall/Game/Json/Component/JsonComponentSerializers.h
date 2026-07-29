#pragma once

#include "Game/Json/Enum/JsonEnumSerializers.h"

#include "Game/Geometory/Triangle.h"
#include "Game/Component/Default/Physics/RectTransform.h"
#include "Game/Component/Default/Physics/Transform.h"
#include "Game/Component/Default/Physics/RigidBody.h"
#include "Game/Component/Default/Renderer/SpriteRenderer.h"
#include "Game/Component/Default/Renderer/ModelRenderer.h"
#include "Game/Component/Default/Renderer/TextRenderer.h"
#include "Game/Component/Default/Collider/Mesh.h"
#include "Game/Component/Default/Collider/Sphere.h"
#include "Game/Component/Camera/TargetCameraController.h"
#include "Game/Component/Player/PlayerStatusController.h"
#include "Game/Component/Player/PlayerController.h"
#include "Game/Component/Enemy/EnemyController.h"
#include "Game/Component/Default/UI/SliderController.h"
#include "Game/Component/Default/UI/SpriteBobbing.h"
#include "Game/Component/Camera/TitleCameraController.h"
#include "Game/Component/Camera/GameCameraController.h"
#include "Game/Component/Default/ScriptableComponent.h"

// Componentから変換
void to_json(ordered_json& j, const Component& component);

// RectTransformから変換
void to_json(json& j, const RectTransform& rectTransfrom);

// Transformから変換
void to_json(json& j, const Transform& transfrom);

// Rigidbodyから変換
void to_json(json& j, const Rigidbody& transfrom);

// SpriteRendererから変換
void to_json(json& j, const SpriteRenderer& spriteRenderer);

// ModelRendererから変換
void to_json(json& j, const ModelRenderer& modelRenderer);

// TextRendererから変換
void to_json(json& j, const TextRenderer& textRenderer);

// Meshから変換
void to_json(json& j, const Mesh& mesh);

// Sphereから変換
void to_json(json& j, const Sphere& sphere);

// TargetCameraから変換
void to_json(json& j, const TargetCameraController& targetCamera);

// SliderControllerから変換
void to_json(json& j, const SliderController& sliderController);

// SpriteBobbingから変換
void to_json(json& j, const SpriteBobbing& spriteBobbing);

// Elementから変換
void to_json(json& j, const ScriptableComponent::Element& element);
// ScriptableComponentから変換
void to_json(json& j, const ScriptableComponent& scritableComponent);

// PlayerControllerから変換
void to_json(json& j, const PlayerController& playerController);

// PlayerStatusControllerから変換
void to_json(json& j, const PlayerStatusController& playerStatusController);

// EnemyControllerから変換
void to_json(json& j, const EnemyController& enemyController);

// StageControllerから変換
void to_json(json& j, const StageController& stageController);

// TitleCameraControllerから変換
void to_json(json& j, const TitleCameraController& titleCameraController);

// GameCameraControllerから変換
void to_json(json& j, const GameCameraController& gameCameraController);
