#pragma once

#include "Game/GameObject/GameObject.h"
#include "Game/Component/Default/Physics/RectTransform.h"
#include "Game/Component/Default/Collider/Collider.h"
#include "Game/Component/Default/Renderer/SpriteRenderer.h"

NLOHMANN_JSON_SERIALIZE_ENUM(ObjectTag, {
	{ ObjectTag::Defaut,	"Default"	},
	{ ObjectTag::Player,	"Player"	},
	{ ObjectTag::Enemy,		"Enemy"		},
	{ ObjectTag::Stage,		"Stage"		}
	}
);

NLOHMANN_JSON_SERIALIZE_ENUM(ColliderType, {
	{ ColliderType::None,	"None"		},
	{ ColliderType::Sphere,	"Sphere"	},
	{ ColliderType::Mesh,	"Mesh"		}
	}
);

NLOHMANN_JSON_SERIALIZE_ENUM(LayerMaskType, {
	{ LayerMaskType::None,		"None"		},
	{ LayerMaskType::Default,	"Default"	},
	{ LayerMaskType::Ball,		"Ball"		},
	{ LayerMaskType::Ground,	"Ground"	}
	}
);

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
