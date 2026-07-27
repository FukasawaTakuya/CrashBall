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

	using DrawInspecterFunc = void(*)(IComponent*);

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
	static void DrawSphere(IComponent* comp);
	// メッシュコライダーの表示
	static void DrawMesh(IComponent* comp);

	// モデルレンダラーの表示
	static void DrawModelRenderer(IComponent* comp);
	// スプライトレンダラーの表示
	static void DrawSpriteRenderer(IComponent* comp);
	// テキストレンダラーの表示
	static void DrawTextRenderer(IComponent* comp);

	// トランスフォームの表示
	static void DrawTransform(IComponent* comp);
	// 2Dトランスフォームの表示
	static void DrawRectTransform(IComponent* comp);
	// 物理演算の表示
	static void DrawRigidbody(IComponent* comp);

	// スライダーの表示
	static void DrawSliderController(IComponent* comp);
	// ボタンの表示
	static void DrawButtonController(IComponent* comp);
	// スライダー浮遊コンポーネントの表示
	static void DrawSpriteBobbing(IComponent* comp);

	// ターゲットカメラの表示
	static void DrawTargetCamera(IComponent* comp);

	// ScriptableObjectの表示
	static void DrawScriptableComponent(IComponent* comp);

	// プレイヤー操作コンポーネントの表示
	static void DrawPlayerController(IComponent* comp);
	// プレイヤーステータス操作コンポーネントの表示
	static void DrawPlayerStateController(IComponent* comp);
	// 敵操作コンポーネントの表示
	static void DrawEnemyController(IComponent* comp);
	// ステージ操作コンポーネントの表示
	static void DrawStageController(IComponent* comp);
	// タイトルカメラ操作コンポーネントの表示
	static void DrawTitleCameraController(IComponent* comp);
	// ゲームカメラ操作コンポーネントの表示
	static void DrawGameCameraController(IComponent* comp);
};
