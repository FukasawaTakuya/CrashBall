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

	using DrawInspecterFunc = void(*)(Component*);
	using DrawPropertyFunc = void(*)(const PropertyInfo&);

	// データメンバの宣言 -----------------------------------------------
private:

	// インスペクター表示関数テーブル
	std::unordered_map<std::type_index, DrawInspecterFunc> m_drawInspecter;
	std::unordered_map<std::type_index, DrawPropertyFunc> m_drawProperty;

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

	void DrawProperty(Component* comp);

	static void DrawBool(const PropertyInfo& property);
	static void DrawInt(const PropertyInfo& property);
	static void DrawFloat(const PropertyInfo& property);
	static void DrawVector2(const PropertyInfo& property);
	static void DrawVector3(const PropertyInfo& property);
	static void DrawQuarternion(const PropertyInfo& property);
	static void DrawColor(const PropertyInfo& property);
	static void DrawSlider(const PropertyInfo& property);
	static void DrawString(const PropertyInfo& property);
	static void DrawGameObject(const PropertyInfo& property);
	static void DrawComponent(const PropertyInfo& property);
	template<typename Enum>
	static void DrawEnum(const PropertyInfo& property);

	// 球コライダーの表示
	static void DrawSphere(Component* comp);
	// メッシュコライダーの表示
	static void DrawMesh(Component* comp);

	// モデルレンダラーの表示
	static void DrawModelRenderer(Component* comp);
	// スプライトレンダラーの表示
	static void DrawSpriteRenderer(Component* comp);
	// テキストレンダラーの表示
	static void DrawTextRenderer(Component* comp);

	// トランスフォームの表示
	static void DrawTransform(Component* comp);
	// 2Dトランスフォームの表示
	static void DrawRectTransform(Component* comp);
	// 物理演算の表示
	static void DrawRigidbody(Component* comp);

	// スライダーの表示
	static void DrawSliderController(Component* comp);
	// ボタンの表示
	static void DrawButtonController(Component* comp);
	// スライダー浮遊コンポーネントの表示
	static void DrawSpriteBobbing(Component* comp);

	// ターゲットカメラの表示
	static void DrawTargetCamera(Component* comp);

	// ScriptableObjectの表示
	static void DrawScriptableComponent(Component* comp);

	// プレイヤー操作コンポーネントの表示
	static void DrawPlayerController(Component* comp);
	// プレイヤーステータス操作コンポーネントの表示
	static void DrawPlayerStateController(Component* comp);
	// 敵操作コンポーネントの表示
	static void DrawEnemyController(Component* comp);
	// ステージ操作コンポーネントの表示
	static void DrawStageController(Component* comp);
	// タイトルカメラ操作コンポーネントの表示
	static void DrawTitleCameraController(Component* comp);
	// ゲームカメラ操作コンポーネントの表示
	static void DrawGameCameraController(Component* comp);
};

inline const char* StringToCharArray(const std::array<std::string_view, 256Ui64>& svArray);

template<typename Enum>
inline void ObjectInspectorGui::DrawEnum(const PropertyInfo& property)
{
	static std::array<const char*, magic_enum::enum_count<Enum>()> enumNames[magic_enum::enum_count<Enum>()]
		= { StringToCharArray<magic_enum::enum_count<Enum>()>(magic_enum::enum_names<Enum>()) };

	int currentOrigin = *static_cast<int*>(property.data);
	auto x = magic_enum::enum_names<Origin>();
	if (ImGui::Combo(property.name.c_str(), &currentOrigin, enumNames->data(), magic_enum::enum_names<Enum>().size()))
	{
		*static_cast<int*>(property.data) = currentOrigin;
	}
}

template<size_t N>
inline std::array<const char*, N> StringToCharArray(const std::array<std::string_view, N>& svArray)
{
	std::array<const char*, N> cArray;

	for (int i = 0; i < N; i++)
	{
		cArray[i] = svArray[i].data();
	}

	return cArray;
}
