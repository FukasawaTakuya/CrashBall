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

/**
 * \brief オブジェクトリスト表示
 */
class  ObjectListGui {

	// データメンバの宣言 -----------------------------------------------
private:

	// 選択中のオブジェクト
	GameObject* m_selectedObject = nullptr;

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
	void Update(std::vector<GameObject*>* gameObjects);

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
