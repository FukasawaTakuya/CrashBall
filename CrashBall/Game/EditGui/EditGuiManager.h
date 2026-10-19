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
#include "SceneSelect.h"

#include "Game/RenderTexture/MyRenderTexture.h"

#include "Game/Scene/Interface/ISceneEditer.h"
#include "Game/ScriptableObject/ScriptableObjectManager.h"

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
	std::unique_ptr<SceneSelect>		m_sceneSelect;			// シーン選択

	bool m_isActive = false;	// 有効フラグ
	bool m_editMode = false;	// 編集モード

	MyRenderTexture* m_gameViewTexture  = nullptr;
	MyRenderTexture* m_debugViewTexture = nullptr;

	std::function<void(void)> m_constantLayoutFunc = []() {};	// レイアウト固定関数

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
		ISceneEditer* sceneEditer,
		ScriptableObjectManager* scriptableObjectManager,
		const ResourceContext& resourceContext);

	void Reset();

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

		m_objectListGui->Reset();
	}

	// 編集モードフラグの設定
	void SetEditMode(bool flag) override
	{
		m_editMode = flag;
	}

	// レンダーテクスチャの設定
	void SetRenderTexture(
		MyRenderTexture* gameViewTexture,
		MyRenderTexture* debugViewTexture)
	{
		m_gameViewTexture  = gameViewTexture;
		m_debugViewTexture = debugViewTexture;
	}

	void RegisterConstantLayout();


	// 内部実装
private:

	// レイアウト固定
	void ConstantLayout();

};
