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

#include "Game/Factory/ComponentFactory.h"
#include "Game/IDGenerator/ComponentIDGenerator.h"
#include "Game/Component/Default/Physics/RectTransform.h"
#include "Game/Component/Default/Renderer/SpriteRenderer.h"
#include "Game/Component/Default/Physics/Transform.h"
#include "Game/Component/Default/Collider/Collider.h"
#include "Game/Component/Default/Renderer/ModelRenderer.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 */
ObjectInspectorGui::ObjectInspectorGui()
{
	m_drawProperty.emplace(PropertyType::Bool,		 [&](const PropertyInfo& propertyInfo) { DrawBool(propertyInfo); });
	m_drawProperty.emplace(PropertyType::Int,		 [&](const PropertyInfo& propertyInfo) { DrawInt(propertyInfo); });
	m_drawProperty.emplace(PropertyType::Float,		 [&](const PropertyInfo& propertyInfo) { DrawFloat(propertyInfo); });
	m_drawProperty.emplace(PropertyType::Angle,		 [&](const PropertyInfo& propertyInfo) { DrawAngle(propertyInfo); });
	m_drawProperty.emplace(PropertyType::Vector2,	 [&](const PropertyInfo& propertyInfo) { DrawVector2(propertyInfo); });
	m_drawProperty.emplace(PropertyType::Vector3,	 [&](const PropertyInfo& propertyInfo) { DrawVector3(propertyInfo); });
	m_drawProperty.emplace(PropertyType::Quaternion, [&](const PropertyInfo& propertyInfo) { DrawQuaternion(propertyInfo); });
	m_drawProperty.emplace(PropertyType::Color,		 [&](const PropertyInfo& propertyInfo) { DrawColor(propertyInfo); });
	m_drawProperty.emplace(PropertyType::Slider,	 [&](const PropertyInfo& propertyInfo) { DrawSlider(propertyInfo); });
	m_drawProperty.emplace(PropertyType::String,	 [&](const PropertyInfo& propertyInfo) { DrawString(propertyInfo); });
	m_drawProperty.emplace(PropertyType::Enum,		 [&](const PropertyInfo& propertyInfo) { DrawEnum(propertyInfo); });
	m_drawProperty.emplace(PropertyType::GameObject, [&](const PropertyInfo& propertyInfo) { DrawGameObject(propertyInfo); });
	m_drawProperty.emplace(PropertyType::Component,  [&](const PropertyInfo& propertyInfo) { DrawComponent(propertyInfo); });

	m_drawEnum.emplace(typeid(Origin),				[&](const std::string& name, void* value) { DrawEnumList<Origin>(name, value); });
	m_drawEnum.emplace(typeid(FillOrigin),			[&](const std::string& name, void* value) { DrawEnumList<FillOrigin>(name, value); });
	m_drawEnum.emplace(typeid(DX11::SpriteEffects), [&](const std::string& name, void* value) { DrawEnumList<DX11::SpriteEffects>(name, value); });
	m_drawEnum.emplace(typeid(ObjectTag),			[&](const std::string& name, void* value) { DrawEnumList<ObjectTag>(name, value); });
	m_drawEnum.emplace(typeid(LayerMaskType),		[&](const std::string& name, void* value) { DrawEnumList<LayerMaskType>(name, value); });
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
void ObjectInspectorGui::Updata(
	GameObject* selectedObject,
	const ResourceContext& resourceContext)
{
	ImGui::Begin("Inspector");

	if (selectedObject != nullptr)
	{
		// アクティブフラグ
		ImGui::Checkbox(" ", &selectedObject->m_isActice);
		ImGui::SameLine();
		// オブジェクト名
		ImGui::InputText("Name", &selectedObject->m_name);
		// タグ
		m_drawEnum[typeid(ObjectTag)]("Tag", &selectedObject->m_tag);

		std::string objName = "##" + selectedObject->GetName();
		ImGui::BeginChild(objName.c_str());

		// コンポーネント表示
		for (auto& comp : *selectedObject->GetComponentsList())
		{
			ImGuiBackendFlags flag = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding;

			ImGui::Separator();

			if (ImGui::TreeNodeEx(comp->GetCompName().c_str(), flag))
			{
				ImGui::SameLine();
				// アクティブフラグ
				ImGui::Checkbox(" ", &comp->m_isActive);

				ImGui::SameLine();

				// コンポーネント削除
				if (ImGui::Button("remove"))
				{
					m_removeCompFunc = [&]() { selectedObject->RemoveComponent(comp.get()); };
				}

				// プロパティ表示
				DrawProperty(comp.get(), resourceContext);
				ImGui::TreePop();
			}
		}

		// コンポーネント削除関数実行
		m_removeCompFunc();
		m_removeCompFunc = []() {};

		// ボタンが押されたとき
		if (ImGui::Button("Add Component"))
		{
			// フラグをオンに
			m_isOpenComponents = !m_isOpenComponents;
		}

		// コンポーネントリスト開閉がオンなら
		if (m_isOpenComponents)
		{
			// コンポーネントリスト表示
			ImGui::BeginChild("Components");

			for (auto& compName : ComponentFactory::GetCompNameList())
			{
				ImGui::Selectable(compName.c_str());

				// 選択された場合
				if (ImGui::IsItemClicked())
				{
					// コンポーネントの作成
					auto comp = ComponentFactory::CreataFromJson(
						compName,
						selectedObject);

					auto ptr = comp.get();
					// コンポーネントのアタッチ
					selectedObject->AddComponent(std::move(comp));
					// IDの設定
					ptr->SetID(ComponentIDGenerator::GetID());
					ptr->Awake();
					// フラグを下げる
					m_isOpenComponents = false;
					break;
				}
			}

			ImGui::EndChild();
		}

		ImGui::EndChild();

	}
	ImGui::End();
}

/**
 * \brief プロパティの表示
 * 
 * \param comp コンポーネント
 * \param resourceContext リソース用のコンテキスト
 */
void ObjectInspectorGui::DrawProperty(
	Component* comp,
	const ResourceContext& resourceContext)
{
	for (auto& property : comp->GetProperties())
	{
		m_drawProperty[property.propType](property);

		// 編集されたら専用関数実行
		if (ImGui::IsItemEdited())
		{
			comp->EditedFunc();
			comp->EditedFunc(resourceContext);
		}
	}
}

// ========================================================================= //
// ========================== プロパティ表示関数一覧 ========================== //
// ========================================================================= //

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
 * \brief Angle型のプロパティ表示
 *
 * \param property プロパティ
 */
void ObjectInspectorGui::DrawAngle(const PropertyInfo& property)
{
	float radian = XMConvertToDegrees(*static_cast<float*>(property.data));

	ImGui::DragFloat(
		property.name.c_str(),
		&radian);

	*static_cast<float*>(property.data) = XMConvertToRadians(radian);
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
		*static_cast<std::wstring*>(property.data) = Utility::ConvertToWideChar(s);
	}
	else if (typeid(std::string) == property.propTypeId)
	{
		ImGui::InputText(
			property.name.c_str(),
			static_cast<std::string*>(property.data));
	}
}

/**
 * \brief 列挙型のプロパティ表示
 *
 * \param property プロパティ
 */
void ObjectInspectorGui::DrawEnum(const PropertyInfo& property)
{
	m_drawEnum[property.propTypeId](property.name, property.data);
}

/**
 * \brief GameObject型のプロパティ表示
 *
 * \param property プロパティ
 */
void ObjectInspectorGui::DrawGameObject(const PropertyInfo& property)
{
	// ゲームオブジェクト情報の表示
	GameObject* gameObject = *static_cast<GameObject**>(property.data);
	std::string objName;
	if (gameObject != nullptr)
	{
		objName = gameObject->GetName();
	}
	else
	{
		objName = "nullPtr(GameObject)";
	}
	ImGui::InputText(
		property.name.c_str(),
		&objName);

	// ドロップされたとき
	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* payload =
			ImGui::AcceptDragDropPayload("DragGameObject");
		if (payload != nullptr)
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
	// コンポーネント情報の表示
	Component* component = *static_cast<Component**>(property.data);
	std::string compName;
	if (component != nullptr)
	{
		compName = component->GetGameObject()->GetName() + "::" + component->GetCompName();
	}
	else
	{
		compName = "nullPtr(Component)";
	}
	ImGui::InputText(
		property.name.c_str(),
		&compName);

	// ドロップされたとき
	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* payload =
			ImGui::AcceptDragDropPayload("DragGameObject");
		if (payload != nullptr)
		{
			// コンポーネントを検索して見つかれば割り当てる
			*static_cast<Component**>(property.data) 
			 = (*(GameObject**)payload->Data)->GetComponent(property.propTypeId);
		}
	}
}
