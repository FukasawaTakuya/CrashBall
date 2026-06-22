#include "pch.h"
#include "JsonSerializers.h"

void DirectX::SimpleMath::to_json(json& j, const Vector2& vec2)
{
	j = json{
		{ "x", vec2.x },
		{ "y", vec2.y }
	};
}

void to_json(json& j, const RectTransform& rectTransfrom)
{
	j = json{
		{ "position", rectTransfrom.m_position	},
		{ "rotate",	  rectTransfrom.m_rotate	},
		{ "scale",	  rectTransfrom.m_scale		},
		{ "origin",   rectTransfrom.m_origin	}
	};
}