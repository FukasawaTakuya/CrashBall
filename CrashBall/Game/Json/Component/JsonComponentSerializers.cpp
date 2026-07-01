#include "pch.h"
#include "JsonComponentSerializers.h"
#include "Game/State/Player/PlayerAttackState.h"
#include "Game/Common/Utility.h"


// RectTransformから変換
void to_json(json& j, const RectTransform& rectTransfrom)
{
	j = json{
		{ "position", rectTransfrom.m_localPosition	},
		{ "rotate",	  rectTransfrom.m_localRotate	},
		{ "scale",	  rectTransfrom.m_localScale	},
		{ "origin",   rectTransfrom.m_origin		}
	};
}

// Transformから変換
void to_json(json& j, const Transform& transfrom)
{
	j = json{
		{ "position",	transfrom.m_localPosition },
		{ "rotate",		transfrom.m_localRotate	 },
		{ "scale",		transfrom.m_localScale	 }
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
		{ "text",		Utility::ConvertToMultiByteChar(textRenderer.m_text)	},
		{ "color",		textRenderer.m_color									},
		{ "fontScale",	textRenderer.m_fontScale								},
		{ "layerDepth", textRenderer.m_layerDepth								},
		{ "fontKey",	textRenderer.m_fontKey									}
	};
}

// Meshから変換
void to_json(json& j, const Mesh& mesh)
{
	j = json{
		{ "type",	  mesh.m_type				},
		{ "layerMaskType", mesh.m_layerMaskType },
		{ "meshData", mesh.m_meshData.c_str()	}
	};
}

// Sphereから変換
void to_json(json& j, const Sphere& sphere)
{
	j = json{
		{ "type",	sphere.m_type				  },
		{ "layerMaskType", sphere.m_layerMaskType },
		{ "radius", sphere.m_radius				  }
	};
}

// TargetCameraから変換
void to_json(json& j, const TargetCamera& targetCamera)
{
	j = json{
		{ "offset", targetCamera.m_offset }
	};
}

// SliderControllerから変換
void to_json(json& j, const SliderController& sliderController)
{
	j = json{
		{ "slideSpeed", sliderController.m_slideSpeed }
	};
}

// PlayerControllerから変換
void to_json(json& j, const PlayerController& playerController)
{
	j = json{
		{ "attackSpeed",	playerController.m_attackSpeed		},
		{ "attackDuration", playerController.m_attackDuration	},
		{ "acceleration",	playerController.m_acceleration		},
		{ "maxSpeed",		playerController.m_maxSpeed			}
	};
}

// PlayerStatusControllerから変換
void to_json(json& j, const PlayerStatusController& playerStatusController)
{
	j = json{
		{ "attackCost",		playerStatusController.m_attackCost		},
		{ "minAttackPower", playerStatusController.m_minAttackPower }
	};
}

// EnemyControllerから変換
void to_json(json& j, const EnemyController& enemyController)
{
	j = json{
		{ "acceleration",			 enemyController.m_acceleration },
		{ "avoidWallDistance",		 enemyController.m_avoidWallDistance },
		{ "avoidWallWeakForce",		 enemyController.m_avoidWallWeakForce },
		{ "avoidWallStrongForce",	 enemyController.m_avoidWallStrongForce },
		{ "maxHp",					 enemyController.m_maxHp },
		{ "directionCircleDistance", enemyController.m_directionCircleDistance },
		{ "directionCircleRadius",	 enemyController.m_directionCircleRadius },
		{ "directionChageInterval",  enemyController.m_directionChageInterval }
	};
}

// StageControllerから変換
void to_json(json& j, const StageController& stageController)
{
	j = json{
		{ "floorNormalY", stageController.m_floorNormalY },
		{ "floorCenterPosY", stageController.m_floorCenterPosY }
	};
}
