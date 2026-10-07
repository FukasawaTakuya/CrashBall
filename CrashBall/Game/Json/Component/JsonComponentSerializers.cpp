#include "pch.h"
#include "JsonComponentSerializers.h"

#include "Game/Json/SimpleMath/JsonSimpleMathConverter.h"
#include "Game/Common/Utility.h"
#include "Library/magic_enum.hpp"

using namespace DirectX;

// PropertyInfoから変換
void to_json(ordered_json& j, const PropertyInfo& property)
{
	j["name"] = property.name;
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
	case PropertyType::Angle:
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
	{
		GameObject* obj = *static_cast<GameObject**>(property.data);
		if (obj != nullptr)
		{
			j["data"] = obj->GetID();
		}
		else
		{
			j["data"] = -99;
		}
	}
		break;
	case PropertyType::Component:
	{
		Component* comp = *static_cast<Component**>(property.data);
		if (comp != nullptr)
		{
			j["data"] = comp->GetID();
		}
		else
		{
			j["data"] = -99;
		}
	}
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
	j["isActive"] = component.GetIsActive();
	j["properties"] = nullptr;

	for (auto& prop : component.GetProperties())
	{
		j["properties"].push_back(prop);
	}
}

// GameObjectから変換
void to_json(ordered_json& j, const GameObject& gameObject)
{
	j["name"]		= gameObject.GetName();
	j["tag"]		= magic_enum::enum_name<ObjectTag>(gameObject.GetTag());
	j["id"]			= gameObject.GetID();
	j["isActive"]	= gameObject.GetIsActive();
	j["components"] = nullptr;
	j["children"]	= nullptr;

	for (auto& comp : *gameObject.GetComponentsList())
	{
		j["components"].push_back(*comp.get());
	}

	for (auto& obj : gameObject.GetChildren())
	{
		j["children"].push_back(obj->GetID());
	}
}
