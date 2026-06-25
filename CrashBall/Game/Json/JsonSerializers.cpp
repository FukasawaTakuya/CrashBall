#include "pch.h"
#include "JsonSerializers.h"


// RectTransformから変換
void to_json(json& j, const RectTransform& rectTransfrom)
{
	j = json{
		{ "position", rectTransfrom.m_position	},
		{ "rotate",	  rectTransfrom.m_rotate	},
		{ "scale",	  rectTransfrom.m_scale		},
		{ "origin",   rectTransfrom.m_origin	}
	};
}

// Transformから変換
void to_json(json& j, const Transform& transfrom)
{
	j = json{
		{ "position",	transfrom.m_position },
		{ "rotate",		transfrom.m_rotate	 },
		{ "scale",		transfrom.m_scale	 }
	};
}

// Rigidbodyから変換
void to_json(json& j, const Rigidbody& rigidbody)
{
	j = json{
		{ "gravityAccelaration", rigidbody.m_gravityAcceleration },
		{ "friction",			 rigidbody.m_friction			 },
		{ "mass",				 rigidbody.m_mass				 },
		{ "isDynamic",			 rigidbody.m_isDynamic			 }
	};
}

// SpriteRendererから変換
void to_json(json& j, const SpriteRenderer& spriteRenderer)
{
	j = json{
		{ "color",			spriteRenderer.m_color			},
		{ "spriteScale",	spriteRenderer.m_spriteScale	},
		{ "layerDepth",		spriteRenderer.m_layerDepth		},
		{ "fillOrigin",		spriteRenderer.m_fillOrigin		},
		{ "spriteEffects",	spriteRenderer.m_spriteEffects	},
		{ "spriteKey",		spriteRenderer.m_spriteKey		}
	};
}

// ModelRendererから変換
void to_json(json& j, const ModelRenderer& modelRenderer)
{
	j = json{
		{ "modelKey", modelRenderer.m_modelKey }
	};
}

// TextRendererから変換
void to_json(json& j, const TextRenderer& textRenderer)
{
	j = json{
		{ "text",		textRenderer.m_text		  },
		{ "color",		textRenderer.m_color	  },
		{ "fontScale",	textRenderer.m_fontScale  },
		{ "layerDepth", textRenderer.m_layerDepth }
	};
}

// Meshから変換
void to_json(json& j, const Mesh& mesh)
{
	j = json{
		{ "meshData", mesh.m_meshData }
	};
}

// Sphereから変換
void to_json(json& j, const Sphere& sphere)
{
	j = json{
		{ "type",	sphere.m_type	},
		{ "radius", sphere.m_radius }
	};
}

// TargetCameraから変換
void to_json(json& j, const TargetCamera& targetCamera)
{
	j = json{
		{ "offset", targetCamera.m_offset }
	};
}

// PlayerStatusControllerから変換
void to_json(json& j, const PlayerStatusController& playerStatusController)
{
	j = json{
		{ "attackCost", playerStatusController.m_ATTACK_COST },
		{ "minAttackPower", playerStatusController.m_MIN_ATTACK_POWER }
	};
}
