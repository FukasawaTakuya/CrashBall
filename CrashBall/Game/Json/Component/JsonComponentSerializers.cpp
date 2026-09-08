#include "pch.h"
#include "JsonComponentSerializers.h"

#include "Game/Json/SimpleMath/JsonSimpleMathConverter.h"
#include "Game/Common/Utility.h"

using namespace DirectX;

// PropertyInfoから変換
void to_json(ordered_json& j, const PropertyInfo& property)
{
	j["name"] = property.name;
	j["type"] = property.propType;
	switch (property.propType)
	{
	case PropertyType::Bool:
		j["data"] = *static_cast<bool*>(property.data);
		break;
	case PropertyType::Int:
		j["data"] = *static_cast<int*>(property.data);
		break;
	case PropertyType::Float:
		j["data"] = *static_cast<float*>(property.data);
		break;
	case PropertyType::Vector2:
		j["data"] = *static_cast<DirectX::SimpleMath::Vector2*>(property.data);
		break;
	case PropertyType::Vector3:
		j["data"] = *static_cast<DirectX::SimpleMath::Vector3*>(property.data);
		break;
	case PropertyType::Quaternion:
		j["data"] = *static_cast<DirectX::SimpleMath::Quaternion*>(property.data);
		break;
	case PropertyType::Color:
		j["data"] = *static_cast<DirectX::SimpleMath::Color*>(property.data);
		break;
	case PropertyType::Slider:
		j["data"] = *static_cast<float*>(property.data);
		break;
	case PropertyType::String:
		// wstringの時はマルチバイト文字に変換する
		if (typeid(std::wstring) == property.propTypeId)
		{
			j["data"] =
				Utility::ConvertToMultiByteChar(*static_cast<std::wstring*>(property.data));
		}
		else if (typeid(std::string) == property.propTypeId)
		{
			j["data"] = *static_cast<std::string*>(property.data);
		}
		break;
	case PropertyType::Enum:
		j["data"] = *static_cast<int*>(property.data);
		break;
	case PropertyType::GameObject:
		j["data"] = (*static_cast<GameObject**>(property.data))->GetID();
		break;
	case PropertyType::Component:
		j["data"] = (*static_cast<Component**>(property.data))->GetID();
		break;
	default:
		break;
	}
}

// Componentから変換
void to_json(ordered_json& j, const Component& component)
{
	j["compName"] = component.GetCompName();
	j["id"] = component.GetID();
	j["properties"] = nullptr;

	for (auto& prop : component.GetProperties())
	{
		j["properties"].push_back(prop);
	}
}

// GameObjectから変換
void to_json(ordered_json& j, const GameObject& gameObject)
{
	j["name"] = gameObject.GetName();
	j["tag"] = gameObject.GetTag();
	j["id"] = gameObject.GetID();
	j["isActive"] = gameObject.GetIsActive();
	j["components"] = nullptr;
	j["children"] = nullptr;

	for (auto& comp : *gameObject.GetComponentsList())
	{
		j["components"].push_back(*comp.get());
	}

	for (auto& obj : gameObject.GetChildren())
	{
		j["children"].push_back(obj->GetID());
	}
}

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
void to_json(json& j, const TargetCameraController& targetCamera)
{
	j = json{
		{ "offset", targetCamera.m_baseOffset }
	};
}

// SliderControllerから変換
void to_json(json& j, const SliderController& sliderController)
{
	j = json{
		{ "slideSpeed", sliderController.m_slideSpeed }
	};
}

// SpriteBobbingから変換
void to_json(json& j, const SpriteBobbing& spriteBobbing)
{
	j = json{
		{ "amplitude", spriteBobbing.m_amplitude },
		{ "frequency", spriteBobbing.m_frequency },
		{ "initPos"	 , spriteBobbing.m_initPos	 }
	};
}

// Elementからの変換
void to_json(json& j, const ScriptableComponent::Element& element)
{
	j["type"] = element.first;
	switch (element.first)
	{
	case ValueType::Float:
		j["value"] = std::get<float>(element.second);
		break;
	case ValueType::Vector2:
		j["value"] = std::get<SimpleMath::Vector2>(element.second);
		break;
	case ValueType::Vector3:
		j["value"] = std::get<SimpleMath::Vector3>(element.second);
		break;
	case ValueType::Color:
		j["value"] = std::get<SimpleMath::Color>(element.second);
		break;
	case ValueType::String:
		j["value"] = std::get<std::string>(element.second);
		break;
	default:
		break;
	}
}

// ScriptableComponentから変換
void to_json(json& j, const ScriptableComponent& scritableComponent)
{
	//for (auto& it : scritableComponent.GetValueList())
	//{
	//	j["elements"].push_back(it);
	//}
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

// TitleCameraControllerから変換
void to_json(json& j, const TitleCameraController& titleCameraController)
{
	j = json{
		{ "offset",			titleCameraController.m_baseOffset		},
		{ "rotateAngleRad", titleCameraController.m_rotateAngeleRad }
	};
}

// GameCameraControllerから変換
void to_json(json& j, const GameCameraController& gameCameraController)
{
	j = json{
		{ "offset",			gameCameraController.m_baseOffset	  },
		{ "rotateAngleRad", gameCameraController.m_rotateAngleRad }
	};
}
