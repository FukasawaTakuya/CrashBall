#pragma once

#include "Game/Component/Default/Component.h"
#include "Game/GameObject/GameObject.h"

/**
 * \brief 基底オブジェクト
 */
class  ObjectInspectorGui {

	using drawInspecterFunc = void(*)(Component*);

	// データメンバの宣言 -----------------------------------------------
private:

	// インスペクター表示関数テーブル
	std::unordered_map<std::type_index, drawInspecterFunc> m_drawInspecter;

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

	// トランスフォームの表示
	static void DrawTransform(Component* comp);
	// トランスフォームの表示
	static void DrawRectTransform(Component* comp);
	// 物理演算の表示
	static void DrawRigidbody(Component* comp);
};
