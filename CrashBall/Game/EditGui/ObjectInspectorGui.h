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

#include "ImGui/imgui.h"
#include "ImGui/imgui_stdlib.h"
#include "Library/magic_enum.hpp"

/**
 * \brief オブジェクトのインスペクター表示
 */
class  ObjectInspectorGui {

	using DrawPropertyFunc = void(*)(const PropertyInfo&);
	using DrawEnumFunc = void(*)(const PropertyInfo&);

	// 列挙型表示関数テーブル
	static std::unordered_map<std::type_index, DrawEnumFunc> s_drawEnum;

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
	static void DrawBool(const PropertyInfo& property);
	// Int型のプロパティ表示
	static void DrawInt(const PropertyInfo& property);
	// Float型のプロパティ表示
	static void DrawFloat(const PropertyInfo& property);
	// Vector2型のプロパティ表示
	static void DrawVector2(const PropertyInfo& property);
	// Vector3型のプロパティ表示
	static void DrawVector3(const PropertyInfo& property);
	// Quarternion型のプロパティ表示
	static void DrawQuaternion(const PropertyInfo& property);
	// Color型のプロパティ表示
	static void DrawColor(const PropertyInfo& property);
	// Slider型のプロパティ表示
	static void DrawSlider(const PropertyInfo& property);
	// String型のプロパティ表示
	static void DrawString(const PropertyInfo& property);
	// Enum型のプロパティ表示
	static void DrawEnum(const PropertyInfo& property);
	// GameObject型のプロパティ表示
	static void DrawGameObject(const PropertyInfo& property);
	// Comonent型のプロパティ表示
	static void DrawComponent(const PropertyInfo& property);

	// 列挙型の表示
	template<typename Enum>
	static void DrawEnumList(const PropertyInfo& property);
};

inline const char* StringViewToCharArray(const std::array<std::string_view, 256Ui64>& svArray);

template<typename Enum>
inline void ObjectInspectorGui::DrawEnumList(const PropertyInfo& property)
{
	static std::array<const char*, magic_enum::enum_count<Enum>()> enumNames[magic_enum::enum_count<Enum>()]
		= { StringViewToCharArray<magic_enum::enum_count<Enum>()>(magic_enum::enum_names<Enum>()) };

	int currentOrigin = *static_cast<int*>(property.data);
	if (ImGui::Combo(property.name.c_str(), &currentOrigin, enumNames->data(), magic_enum::enum_names<Enum>().size()))
	{
		*static_cast<int*>(property.data) = currentOrigin;
	}
}

template<size_t N>
inline std::array<const char*, N> StringViewToCharArray(const std::array<std::string_view, N>& svArray)
{
	std::array<const char*, N> cArray;

	for (int i = 0; i < N; i++)
	{
		cArray[i] = svArray[i].data();
	}

	return cArray;
}
