/*****************************************************************//**
 * \file   ObjectInspectorGui.cpp
 * \brief  オブジェクトのインスペクター表示
 *
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#include "pch.h"
#include "ObjectInspectorGui.h"
#include "Library/magic_enum.hpp"

#include "ImGui/imgui.h"
#include "ImGui/imgui_stdlib.h"
#include "Game/Common/Utility.h"

#include "Game/Component/Default/Physics/Transform.h"
#include "Game/Component/Default/Physics/RectTransform.h"
#include "Game/Component/Default/Physics/RigidBody.h"
#include "Game/Component/Default/Collider/Sphere.h"
#include "Game/Component/Default/Collider/Mesh.h"
#include "Game/Component/Default/Renderer/ModelRenderer.h"
#include "Game/Component/Default/Renderer/SpriteRenderer.h"
#include "Game/Component/Default/Renderer/TextRenderer.h"
#include "Game/Component/Default/UI/SliderController.h"
#include "Game/Component/Default/UI/ButtonController.h"
#include "Game/Component/Default/UI/SpriteBobbing.h"
#include "Game/Component/Camera/TargetCameraController.h"
#include "Game/Component/Default/ScriptableComponent.h"

#include "Game/Component/Player/PlayerController.h"
#include "Game/Component/Player/PlayerStatusController.h"
#include "Game/Component/Enemy/EnemyController.h"
#include "Game/Component/Stage/StageController.h"
#include "Game/Component/Camera/TitleCameraController.h"
#include "Game/Component/Camera/GameCameraController.h"

using namespace DirectX;

using DrawEnumFunc = void(*)(const PropertyInfo&);
std::unordered_map<std::type_index, DrawEnumFunc> ObjectInspectorGui::s_drawEnum = {};

/**
 * \brief コンストラクタ
 * 
 */
ObjectInspectorGui::ObjectInspectorGui()
{
	m_drawProperty.emplace(PropertyType::Bool, DrawBool);
	m_drawProperty.emplace(PropertyType::Int, DrawInt);
	m_drawProperty.emplace(PropertyType::Float, DrawFloat);
	m_drawProperty.emplace(PropertyType::Vector2, DrawVector2);
	m_drawProperty.emplace(PropertyType::Vector3, DrawVector3);
	m_drawProperty.emplace(PropertyType::Quaternion, DrawQuaternion);
	m_drawProperty.emplace(PropertyType::Color, DrawColor);
	m_drawProperty.emplace(PropertyType::Slider, DrawSlider);
	m_drawProperty.emplace(PropertyType::String, DrawString);
	m_drawProperty.emplace(PropertyType::Enum, DrawEnum);
	m_drawProperty.emplace(PropertyType::GameObject, DrawGameObject);
	m_drawProperty.emplace(PropertyType::Component, DrawComponent);

	ObjectInspectorGui::s_drawEnum.emplace(typeid(Origin), DrawEnumList<Origin>);
	ObjectInspectorGui::s_drawEnum.emplace(typeid(FillOrigin), DrawEnumList<FillOrigin>);
	ObjectInspectorGui::s_drawEnum.emplace(typeid(DX11::SpriteEffects), DrawEnumList<DX11::SpriteEffects>);
}

/**
 * \brief デストラクタ
 * 
 */
ObjectInspectorGui::~ObjectInspectorGui()
{
}

/**
 * \brief 更新
 * 
 * \param selectedObject 選択中のオブジェクト
 */
void ObjectInspectorGui::Updata(GameObject* selectedObject)
{
	ImGui::Begin("Inspector");

	if (selectedObject != nullptr)
	{
		ImGui::InputText("Name", &selectedObject->m_name);
		ImGui::InputInt("ID", &selectedObject->m_id);

		ImGui::BeginChild(selectedObject->GetName().c_str());

		for (auto& comp : *selectedObject->GetComponentsList())
		{
			ImGuiBackendFlags flag = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding;

			ImGui::Separator();

			if (ImGui::TreeNodeEx(comp->GetCompName().c_str(), flag))
			{
				DrawProperty(comp.get());
				ImGui::TreePop();
			}
		}
		// 後で消す
		for (auto& child : selectedObject->GetChildren())
		{
			ImGui::Text(child->GetName().c_str());
		}

		ImGui::EndChild();
	}

	ImGui::End();
}

/**
 * \brief プロパティの表示
 * 
 * \param comp コンポーネント
 */
void ObjectInspectorGui::DrawProperty(Component* comp)
{
	for (auto& property : comp->GetProperties())
	{
		m_drawProperty[property.propType](property);
	}
}

/**
 * \brief Bool型のプロパティ表示
 * 
 * \param property プロパティ
 */
void ObjectInspectorGui::DrawBool(const PropertyInfo& property)
{
	ImGui::Checkbox(
		property.name.c_str(),
		static_cast<bool*>(property.data));
}

/**
 * \brief Int型のプロパティ表示
 *
 * \param property プロパティ
 */
void ObjectInspectorGui::DrawInt(const PropertyInfo& property)
{
	ImGui::DragInt(
		property.name.c_str(),
		static_cast<int*>(property.data));
}

/**
 * \brief Float型のプロパティ表示
 *
 * \param property プロパティ
 */
void ObjectInspectorGui::DrawFloat(const PropertyInfo& property)
{
	ImGui::DragFloat(
		property.name.c_str(),
		static_cast<float*>(property.data));
}

/**
 * \brief Vector2型のプロパティ表示
 *
 * \param property プロパティ
 */
void ObjectInspectorGui::DrawVector2(const PropertyInfo& property)
{
	ImGui::DragFloat2(
		property.name.c_str(),
		&(*static_cast<SimpleMath::Vector2*>(property.data)).x);
}

/**
 * \brief Veccor3型のプロパティ表示
 *
 * \param property プロパティ
 */
void ObjectInspectorGui::DrawVector3(const PropertyInfo& property)
{
	ImGui::DragFloat3(
		property.name.c_str(),
		&(*static_cast<SimpleMath::Vector3*>(property.data)).x);
}

/**
 * \brief Quaternion型のプロパティ表示
 *
 * \param property プロパティ
 */
void ObjectInspectorGui::DrawQuaternion(const PropertyInfo& property)
{
	// Vector3型に直す
	SimpleMath::Vector3 v3 = static_cast<SimpleMath::Quaternion*>(property.data)->ToEuler();
	// 度数表記に直す
	v3.x = XMConvertToDegrees(v3.x);
	v3.y = XMConvertToDegrees(v3.y);
	v3.z = XMConvertToDegrees(v3.z);
	// 表示
	ImGui::DragFloat3(
		property.name.c_str(),
		&v3.x);
	// 弧度法に直す
	v3.x = XMConvertToRadians(v3.x);
	v3.y = XMConvertToRadians(v3.y);
	v3.z = XMConvertToRadians(v3.z);
	// Quarternion型に直す
	*static_cast<SimpleMath::Quaternion*>(property.data) =
		SimpleMath::Quaternion::CreateFromYawPitchRoll(v3);
}

/**
 * \brief Color型のプロパティ表示
 *
 * \param property プロパティ
 */
void ObjectInspectorGui::DrawColor(const PropertyInfo& property)
{
	ImGui::ColorEdit4(
		property.name.c_str(),
		&(*static_cast<SimpleMath::Color*>(property.data)).x);
}

/**
 * \brief Slider型のプロパティ表示
 *
 * \param property プロパティ
 */
void ObjectInspectorGui::DrawSlider(const PropertyInfo& property)
{
	ImGui::SliderFloat(
		property.name.c_str(),
		static_cast<float*>(property.data), 0.0f, 1.0f);
}

/**
 * \brief Bool型のプロパティ表示
 *
 * \param property プロパティ
 */
void ObjectInspectorGui::DrawString(const PropertyInfo& property)
{
	// wstringの時はマルチバイト文字に変換する
	if (typeid(std::wstring) == property.propTypeId)
	{
		std::string s = Utility::ConvertToMultiByteChar(*static_cast<std::wstring*>(property.data));
		ImGui::InputText(
			property.name.c_str(),
			&s);
	}
	else if (typeid(std::string) == property.propTypeId)
		ImGui::InputText(
			property.name.c_str(),
			static_cast<std::string*>(property.data));
}

/**
 * \brief Enum型のプロパティ表示
 *
 * \param property プロパティ
 */
void ObjectInspectorGui::DrawEnum(const PropertyInfo& property)
{
	s_drawEnum[property.propTypeId](property);
}

/**
 * \brief GameObject型のプロパティ表示
 *
 * \param property プロパティ
 */
void ObjectInspectorGui::DrawGameObject(const PropertyInfo& property)
{
	GameObject* gameObject = *static_cast<GameObject**>(property.data);
	std::string s;
	if (gameObject != nullptr)
	{
		s = gameObject->GetName();
	}
	else
	{
		s = "nullPtr";
	}
	ImGui::InputText(
		property.name.c_str(),
		&s);

	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload =
			ImGui::AcceptDragDropPayload("DragGameObject"))
		{
			*static_cast<GameObject**>(property.data) = *(GameObject**)payload->Data;
		}
	}
}

/**
 * \brief Component型のプロパティ表示
 *
 * \param property プロパティ
 */
void ObjectInspectorGui::DrawComponent(const PropertyInfo& property)
{
	Component* component = *static_cast<Component**>(property.data);
	std::string s;
	if (component != nullptr)
	{
		s = component->GetGameObject()->GetName() + "::" + component->GetCompName();
	}
	else
	{
		s = "nullPtr";
	}
	ImGui::InputText(
		property.name.c_str(),
		&s);

	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload =
			ImGui::AcceptDragDropPayload("DragGameObject"))
		{
			*static_cast<Component**>(property.data) 
			 = (*(GameObject**)payload->Data)->GetComponent(property.propTypeId);
		}
	}

}
