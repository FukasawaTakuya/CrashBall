/*****************************************************************//**
 * \file   ObjectListGui.h
 * \brief  オブジェクトリスト表示
 * 
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#pragma once

#include "ImGui/imgui.h"

#include "Game/GameObject/GameObject.h"
#include "Game/Scene/Interface/ISceneEditer.h"

/**
 * \brief オブジェクトリスト表示
 */
class  ObjectListGui {

	// データメンバの宣言 -----------------------------------------------
private:

	// 選択中のオブジェクト
	GameObject* m_selectedObject = nullptr;

	// 子オブジェクト生成関数
	std::function<void(GameObject*)> m_AddChildFunc = [](GameObject*) {};

	bool m_isCreate2dObject = false;
	bool m_isCreate3dObject = false;
	std::string m_newObejctName;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	ObjectListGui();

	// デストラクタ
	~ObjectListGui();

	// 操作
public:

	// 更新 
	void Update(ISceneEditer* sceneEditer);

	void Reset();

	// 取得/設定
public:

	// 選択中のオブジェクトの取得
	GameObject* GetSelectedObject()
	{
		return m_selectedObject;
	}

	// 内部実装
private:

	// オブジェクトの表示
	void DrawObjectGui(GameObject* object);
};
