#pragma once

#include "Game/Geometory/Triangle.h"
#include "Game/Component/Default/Physics/RectTransform.h"

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
	});

namespace DirectX::SimpleMath
{
	void to_json(json & j, const Vector2 & vector2);
}

void to_json(json& j, const RectTransform& rectTransfrom);
