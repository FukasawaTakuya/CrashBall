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
#include "Interface/EditButton.h"

#include "Game/Scene/Interface/ISceneEditer.h"

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
	std::unique_ptr<EditButton>			m_editButton;			// 編集ボタン

	ISceneEditer* m_pSceneEditer = nullptr;

	bool m_isActive = false;	// 有効フラグ

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	EditGuiManager(ISceneEditer* pSceneEditer);

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

	bool GetIsActive() const
	{
		return m_isActive;
	}

	RECT GetGameViewRect() const
	{
		return m_gameViewRenderer->GetGameViewRect();
	}

	void SetIsActive(bool flag)
	{
		m_isActive = flag;

		if (!flag)
			m_pSceneEditer->SetEditMode(false);
	}

	// 内部実装
private:

};
