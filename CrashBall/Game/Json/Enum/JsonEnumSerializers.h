#pragma once

#include "Game/GameObject/GameObject.h"
#include "Game/Component/Default/Component.h"
#include "Game/Component/Default/Physics/RectTransform.h"
#include "Game/Component/Default/Collider/Collider.h"
#include "Game/Component/Default/Renderer/SpriteRenderer.h"
#include "Game/Component/Default/ScriptableComponent.h"

NLOHMANN_JSON_SERIALIZE_ENUM(ObjectTag, {
	{ ObjectTag::Default,	"Default"	},
	{ ObjectTag::Player,	"Player"	},
	{ ObjectTag::Enemy,		"Enemy"		},
	{ ObjectTag::Stage,		"Stage"		}
	}
);

NLOHMANN_JSON_SERIALIZE_ENUM(PropertyType, {
	{ PropertyType::Int,		"Int"			},
	{ PropertyType::Bool,		"Bool"			},
	{ PropertyType::Float,		"Float"			},
	{ PropertyType::Vector2,	"Vector2"		},
	{ PropertyType::Vector3,	"Vector3"		},
	{ PropertyType::Quaternion, "Quaternion"	},
	{ PropertyType::Color,		"Color"			},
	{ PropertyType::Slider,		"Slider"		},
	{ PropertyType::String,		"String"		},
	{ PropertyType::Enum,		"Enum"			},
	{ PropertyType::GameObject,	"GameObject"	},
	{ PropertyType::Component,	"Componet"		}
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


NLOHMANN_JSON_SERIALIZE_ENUM(ValueType, {
	{ ValueType::Float,		"CenterTop"	},
	{ ValueType::Vector2,	"Vector2"	},
	{ ValueType::Vector3,	"Vector3"	},
	{ ValueType::Color,		"Color"		},
	{ ValueType::String,	"String"	}
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
