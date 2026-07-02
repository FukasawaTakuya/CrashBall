/*****************************************************************//**
 * \file   ObjectEditGui.h
 * \brief  オブジェクト編集GUI
 * 
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#pragma once

#include "ImGui/imgui.h"
#include "Interface/IObjectEditGui.h"

/**
 * \brief オブジェクト編集GUI
 */
class  ObjectEditGui : public IObjectEditGui {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	// 表示するオブジェクトリスト
	std::vector<GameObject*>* m_objects = nullptr;

	// 選択中のオブジェクト
	GameObject* m_selectedObject = nullptr;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	ObjectEditGui();

	// デストラクタ
	~ObjectEditGui();

	// 操作
public:

	// 更新
	void Update();

	// 取得/設定
public:

	// オブジェクトリストの設定
	void SetObejcts(std::vector<GameObject*>* objects) override
	{
		m_objects = objects;
	}

	// 内部実装
private:

	//
	void DrawObjectGui(GameObject* object);

};
