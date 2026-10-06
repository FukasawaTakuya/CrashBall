/*****************************************************************//**
 * \file   ObjectInspectorGui.h
 * \brief  オブジェクトのインスペクター表示
 * 
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"
#include "Game/GameObject/GameObject.h"
#include "Game/Common/Utility.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_stdlib.h"
#include "Library/magic_enum.hpp"

/**
 * \brief オブジェクトのインスペクター表示
 */
class  ObjectInspectorGui {

	using DrawPropertyFunc = const std::function<void(const PropertyInfo&)>;
	using DrawEnumFunc = const std::function<void(const std::string&, void*)>;

	// 列挙型表示関数テーブル
	std::unordered_map<std::type_index, DrawEnumFunc> m_drawEnum;

	// データメンバの宣言 -----------------------------------------------
private:

	// プロパティ表示関数テーブル
	std::unordered_map<PropertyType, DrawPropertyFunc> m_drawProperty;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	ObjectInspectorGui();

	// デストラクタ
	~ObjectInspectorGui();

	// 操作
public:

	// 更新
	void Updata(GameObject* selectedObject);

	// 取得/設定
public:

	// 内部実装
private:

	// プロパティの表示
	void DrawProperty(Component* comp); 

	// Bool型のプロパティ表示
	void DrawBool(const PropertyInfo& property);
	// Int型のプロパティ表示
	void DrawInt(const PropertyInfo& property);
	// Float型のプロパティ表示
	void DrawFloat(const PropertyInfo& property);
	// Angle型のプロパティ表示
	void DrawAngle(const PropertyInfo& property);
	// Vector2型のプロパティ表示
	void DrawVector2(const PropertyInfo& property);
	// Vector3型のプロパティ表示
	void DrawVector3(const PropertyInfo& property);
	// Quarternion型のプロパティ表示
	void DrawQuaternion(const PropertyInfo& property);
	// Color型のプロパティ表示
	void DrawColor(const PropertyInfo& property);
	// Slider型のプロパティ表示
	void DrawSlider(const PropertyInfo& property);
	// String型のプロパティ表示
	void DrawString(const PropertyInfo& property);
	// 列挙型のプロパティ表示
	void DrawEnum(const PropertyInfo& property);
	// GameObject型のプロパティ表示
	void DrawGameObject(const PropertyInfo& property);
	// Comonent型のプロパティ表示
	void DrawComponent(const PropertyInfo& property);

	template<typename Enum>
	void DrawEnumList(const std::string& name, void* value);
};

// 列挙型の表示
template<typename Enum>
void ObjectInspectorGui::DrawEnumList(const std::string& name, void* value)
{
	auto names = magic_enum::enum_names<Enum>();
	std::string current = names[*static_cast<int*>(value)].data();
	if (ImGui::BeginCombo(name.c_str(), current.c_str()))
	{
		for (int i = 0; i < names.size(); i++)
		{
			bool isSelected = i == *static_cast<int*>(value);
			if (ImGui::Selectable(names[i].data(), &isSelected))
			{
				*static_cast<int*>(value) = i;
			}

			if (isSelected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}

		ImGui::EndCombo();
	}
}
