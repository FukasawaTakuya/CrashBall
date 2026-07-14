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

/**
 * \brief オブジェクトのインスペクター表示
 */
class  ObjectInspectorGui {

	using DrawInspecterFunc = void(*)(Component*);

	// データメンバの宣言 -----------------------------------------------
private:

	// インスペクター表示関数テーブル
	std::unordered_map<std::type_index, DrawInspecterFunc> m_drawInspecter;

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
