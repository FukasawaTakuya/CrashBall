#include "pch.h"
#include "JsonSerializers.h"

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
		{ "width",			spriteRenderer.m_width			},
		{ "height",			spriteRenderer.m_height			},
		{ "spriteScale",	spriteRenderer.m_spriteScale	},
		{ "layerDepth",		spriteRenderer.m_layerDepth		},
		{ "fillOrigin",		spriteRenderer.m_fillOrigin		},
		{ "spriteEffects",	spriteRenderer.m_spriteEffects	},
		{ "spriteKey",		spriteRenderer.m_spriteKey		}
	};
}
