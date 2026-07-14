/*****************************************************************//**
 * \file   EditGuiManager.h
 * \brief  エディタGUI管理
 * 
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/
#pragma once


#include "Interface/IEditModeChanger.h"

#include "ObjectListGui.h"
#include "ObjectInspectorGui.h"
#include "GameViewRenderer.h"
#include "EditButton.h"

#include "Game/RenderTexture/RenderTexture.h"

#include "Game/Scene/Interface/ISceneEditer.h"
#include "Game/Json/IJsonDataManager.h"

/**
 * \brief エディタGUI管理
 */
class  EditGuiManager : public IEditModeChanger
{

	// データメンバの宣言 -----------------------------------------------
private:

	std::unique_ptr<ObjectListGui>      m_objectListGui;		// オブジェクトリスト
	std::unique_ptr<ObjectInspectorGui> m_objectInspectorGui;	// インスペクター
	std::unique_ptr<GameViewRenderer>   m_gameViewRenderer;		// ゲームビュー
	std::unique_ptr<EditButton>			m_editButton;			// 編集ボタン

	bool m_isActive = false;	// 有効フラグ
	bool m_editMode = false;	// 編集モード

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	EditGuiManager(
		ISceneEditer*		pSceneEditer,
		IJsonDataManager*	pJsonDataManager);

	// デストラクタ
	~EditGuiManager();

	// 操作
public:

	// 更新
	void Update(
		std::vector<GameObject*>* gameObjects,
		ID3D11ShaderResourceView* srv);

	// 取得/設定
public:

	// アクティブフラグの取得
	bool GetIsActive() const 
	{
		return m_isActive;
	}

	// 編集モードフラグの取得
	bool GetEditMode() const override
	{
		return m_editMode;
	}

	// ゲームビューの描画領域の取得
	RECT GetGameViewRect() const
	{
		return m_gameViewRenderer->GetGameViewRect();
	}

	// アクティブフラグの設定
	void SetIsActive(bool flag)
	{
		m_isActive = flag;

		// オフなら編集モードフラグもオフにする
		if (flag == false)
			m_editMode = false;
	}

	// 編集モードフラグの設定
	void SetEditMode(bool flag) override
	{
		m_editMode = flag;
	}

	// 内部実装
private:

};
