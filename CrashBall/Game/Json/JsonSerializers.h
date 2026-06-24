#pragma once

#include "Game/Geometory/Triangle.h"
#include "Game/Component/Default/Physics/RectTransform.h"
#include "Game/Component/Default/Physics/Transform.h"
#include "Game/Component/Default/Physics/RigidBody.h"
#include "Game/Component/Default/Renderer/SpriteRenderer.h"
#include "Game/Component/Default/Renderer/ModelRenderer.h"
#include "Game/Component/Default/Renderer/TextRenderer.h"
#include "Game/Component/Default/Collider/Mesh.h"
#include "Game/Component/Default/Collider/Sphere.h"
#include "Game/Component/Camera/TargetCamera.h"
#include "Game/Component/Player/PlayerStatusController.h"

using namespace nlohmann;

NLOHMANN_JSON_SERIALIZE_ENUM(Origin, {
	{ Origin::CenterTop,	"CenterTop"		},
	{ Origin::Center,		"Center"		},
	{ Origin::CenterBottom, "CenterBottom"	},
	{ Origin::LeftCenter,	"LeftCenter"	},
	{ Origin::LeftBottom,	"LeftBottom"	},
	{ Origin::RightTop,		"RightTop"		},
	{ Origin::RightCenter,	"RightCenter"	},
	{ Origin::RightBottom,	"RightBottom"	}
	}
);

NLOHMANN_JSON_SERIALIZE_ENUM(FillOrigin, {
	{ FillOrigin::Center,			"CenterTop"			},
	{ FillOrigin::CenterHorizon,	"CenterHorizon"		},
	{ FillOrigin::CenterVertical,	"CenterVertical"	},
	{ FillOrigin::Left,				"Left"				},
	{ FillOrigin::Top,				"Top"				},
	{ FillOrigin::Right,			"Right"				},
	{ FillOrigin::Bottom,			"Bottom"			}
	});

namespace DirectX::DX11
{
	NLOHMANN_JSON_SERIALIZE_ENUM(SpriteEffects, {
		{ SpriteEffects::SpriteEffects_None,				"None"			},
		{ SpriteEffects::SpriteEffects_FlipHorizontally,	"Horizontally"  },
		{ SpriteEffects::SpriteEffects_FlipVertically,		"Vertically"	},
		{ SpriteEffects::SpriteEffects_FlipBoth,			"Both"			},
		});
}

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
void to_json(json& j, const TargetCamera& targetCamera);

// PlayerStatusControllerから変換
void to_json(json& j, const PlayerStatusController& playerStatusController);
