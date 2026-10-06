#include "pch.h"
#include "JsonComponentDeserializers.h"

#include "Game/Json/SimpleMath/JsonSimpleMathConverter.h"

#include "Game/Common/Utility.h"
#include "Library/magic_enum.hpp"

using namespace DirectX;

// PropertyInfoへ変換
void from_json(const ordered_json& j, PropertyInfo& property)
{
	PropertyType propType
		= magic_enum::enum_cast<PropertyType>(j["type"].get<std::string>()).value();

	switch (propType)
	{
	case PropertyType::Bool:
		*static_cast<bool*>(property.data) = j["data"];
		break;
	case PropertyType::Int:
		*static_cast<int*>(property.data) = j["data"];
		break;
	case PropertyType::Float:
		*static_cast<float*>(property.data) = j["data"];
		break;
	case PropertyType::Angle:
		*static_cast<float*>(property.data) = j["data"];
		break;
	case PropertyType::Vector2:
		*static_cast<DirectX::SimpleMath::Vector2*>(property.data) = j["data"];
		break;
	case PropertyType::Vector3:
		*static_cast<DirectX::SimpleMath::Vector3*>(property.data) = j["data"];
		break;
	case PropertyType::Quaternion:
		*static_cast<DirectX::SimpleMath::Quaternion*>(property.data) = j["data"];
		break;
	case PropertyType::Color:
		*static_cast<DirectX::SimpleMath::Color*>(property.data) = j["data"];
		break;
	case PropertyType::Slider:
		*static_cast<float*>(property.data) = j["data"];
		break;
	case PropertyType::String:
		// wstringの時はマルチバイト文字に変換する]
		if (typeid(std::wstring) == property.propTypeId)
		{
			*static_cast<std::wstring*>(property.data) =
				Utility::ConvertToWideChar(j["data"]);
		}
		else if (typeid(std::string) == property.propTypeId)
		{
			*static_cast<std::string*>(property.data) = j["data"];
		}
		break;
	case PropertyType::Enum:
		*static_cast<int*>(property.data) = j["data"];
		break;
	case PropertyType::GameObject:
		*static_cast<int*>(property.data) = j["data"];
		break;
	case PropertyType::Component:
		*static_cast<int*>(property.data) = j["data"];
		break;
	default:
		break;
	}
}

// Componentへ変換
void from_json(const ordered_json& j, Component& component)
{
	component.SetID(j["id"]);
	component.SetIsActive(j["isActive"]);
	auto& properties = component.GetProperties();

	for (int i = 0; i < j["properties"].size(); i++)
	{
		PropertyType propType 
			= magic_enum::enum_cast<PropertyType>(j["properties"].at(i)["type"].get<std::string>()).value();
		json propData = j["properties"].at(i)["data"];
		
		auto& prop = properties[i];

		switch (propType)
		{
		case PropertyType::Bool:
			*static_cast<bool*>(prop.data) = propData;
			break;
		case PropertyType::Int:
			*static_cast<int*>(prop.data) = propData;
			break;
		case PropertyType::Float:
			*static_cast<float*>(prop.data) = propData;
			break;
		case PropertyType::Angle:
			*static_cast<float*>(prop.data) = propData;
			break;
		case PropertyType::Vector2:
			*static_cast<DirectX::SimpleMath::Vector2*>(prop.data) = propData;
			break;
		case PropertyType::Vector3:
			*static_cast<DirectX::SimpleMath::Vector3*>(prop.data) = propData;
			break;
		case PropertyType::Quaternion:
			*static_cast<DirectX::SimpleMath::Quaternion*>(prop.data) = propData;
			break;
		case PropertyType::Color:
			*static_cast<DirectX::SimpleMath::Color*>(prop.data) = propData;
			break;
		case PropertyType::Slider:
			*static_cast<float*>(prop.data) = propData;
			break;
		case PropertyType::String:
			// wstringの時はマルチバイト文字に変換する
			if (typeid(std::wstring) == prop.propTypeId)
			{
				*static_cast<std::wstring*>(prop.data) =
					Utility::ConvertToWideChar(propData);
			}
			else if (typeid(std::string) == prop.propTypeId)
			{
				*static_cast<std::string*>(prop.data) = propData;
			}
			break;
		case PropertyType::Enum:
			*static_cast<int*>(prop.data) = propData;
			break;
		case PropertyType::GameObject:
			if (*static_cast<GameObject**>(prop.data) == nullptr)
			{
				*static_cast<int*>(prop.data) = propData;
			}
			break;
		case PropertyType::Component:
			if (*static_cast<Component**>(prop.data) == nullptr)
			{
				*static_cast<int*>(prop.data) = propData;
			}
			break;
		default:
			break;
		}
	}
}


// GameObjectへ変換
void from_json(const ordered_json& j, GameObject& gameObject)
{
	gameObject.SetName(j["name"]);
	gameObject.SetTag(magic_enum::enum_cast<ObjectTag>(j["tag"].get<std::string>()).value());
	gameObject.SetID(j["id"]);
	gameObject.SetIsActive(j["isActive"]);

	for (auto& jsonComp : j["components"])
	{
		auto newComp = ComponentFactory::CreataFromJson(jsonComp["compName"], &gameObject);

		Component* compPtr = gameObject.GetComponent(typeid(*newComp));

		if (compPtr == nullptr)
		{
			jsonComp.get_to<Component>(*newComp);
			gameObject.AddComponent(std::move(newComp));
		}
		else
		{
			jsonComp.get_to<Component>(*compPtr);
		}
	}
}

// Traingleへ変換
void from_json(const json& j, Triangle& triangle)
{
	j.at("point1").get_to(triangle.m_point[0]);
	j.at("point2").get_to(triangle.m_point[1]);
	j.at("point3").get_to(triangle.m_point[2]);
}