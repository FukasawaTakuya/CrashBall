/*****************************************************************//**
 * \file   EditGuiManager.h
 * \brief  エディタGUI管理クラス
 * 
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/
#pragma once

#include "ObjectListGui.h"
#include "ObjectInspectorGui.h"
#include "GameViewRenderer.h"
#include "Game/RenderTexture/RenderTexture.h"

/**
 * \brief エディタGUI管理クラス
 */
class  EditGuiManager {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	std::unique_ptr<ObjectListGui>      m_objectListGui;		// オブジェクトリスト
	std::unique_ptr<ObjectInspectorGui> m_objectInspectorGui;	// インスペクター
	std::unique_ptr<GameViewRenderer>   m_gameViewRenderer;		// ゲームビュー

	bool m_isEditMode = false;	// エディタモードか

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	EditGuiManager();

	// デストラクタ
	~EditGuiManager();

	// 操作
public:

	// 更新
	void Update(
		std::vector<GameObject*>* gameObjects,
		std::vector<GameObject*>* scriptableObjects,
		ID3D11ShaderResourceView* srv);

	// 取得/設定
public:

	bool GetIsEditMode() const
	{
		return m_isEditMode;
	}

	RECT GetGameViewRect() const
	{
		return m_gameViewRenderer->GetGameViewRect();
	}

	void SetIsEditMode(bool flag)
	{
		m_isEditMode = flag;
	}

	// 内部実装
private:

};
