/*****************************************************************//**
 * \file   ObjectListGui.h
 * \brief  オブジェクト編集GUI
 * 
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#pragma once

#include "ImGui/imgui.h"
#include "Interface/IObjectListGui.h"

/**
 * \brief オブジェクト編集GUI
 */
class  ObjectListGui : public IObjectListGui {

	// データメンバの宣言 -----------------------------------------------
private:

	// 表示するオブジェクトリスト
	std::vector<GameObject*>* m_gameObjects = nullptr;

	// 表示するスクリプタブルオブジェクトリスト
	std::vector<const GameObject*>* m_scriptableObjects = nullptr;

	// 選択中のオブジェクト
	const GameObject* m_selectedObject = nullptr;

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
	void Update();

	// 取得/設定
public:

	// 選択中のオブジェクトの取得
	const GameObject* GetSelectedObject()
	{
		return m_selectedObject;
	}

	// オブジェクトリストの設定
	void SetGameObejcts(std::vector<GameObject*>* objects) override
	{
		m_gameObjects = objects;
	}

	// スクリプタブルオブジェクトリストの設定
	void SetScriptableObjects(std::vector<const GameObject*>* objects) override
	{
		m_scriptableObjects = objects;
	}

	// 内部実装
private:

	// オブジェクトの表示
	void DrawObjectGui(const GameObject* object);
};
