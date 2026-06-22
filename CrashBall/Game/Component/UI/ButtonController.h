/*****************************************************************//**
 * \file   ButtonController.h
 * \brief  ボタン操作コンポーネント
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"
#include "Game/Component/Default/Physics/RectTransform.h"
#include "Game/Component/Default/Renderer/SpriteRenderer.h"
#include "Game/Component/Default/Renderer/TextRenderer.h"

/**
 * @brief ボタン操作コンポーネント
 */
class  ButtonController : public Component {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	std::function<void()> m_onPushCommand = [](){};			// 押されたときの処理
	std::function<void()> m_onDrugCommand = [](){};			// ドラック中の処理

	std::function<void()> m_onHoverEnterCommand = [](){};	// ホバー時の処理
	std::function<void()> m_onHoverStayCommand  = [](){};	// ホバー中の処理
	std::function<void()> m_onHoverExitCommand  = [](){};	// ホバー離脱の処理

	bool m_isOnClick	= false;	// クリックされたか
	bool m_isOnRelease	= false;	// ボタンが離されたか
	bool m_isPush		= false;	// 押されたか

	bool m_isHover		= false;	// ホバー状態か
	bool m_prevIsHover  = false;	// 前フレームのホバー状態

	// コンポーネントのキャッシュ
	RectTransform*  m_rectTransform  = nullptr;
	SpriteRenderer* m_spriteRenderer = nullptr;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	ButtonController(IGameObject* gameObject);

	// デストラクタ
	~ButtonController();

	// 操作
public:

	// 更新
	void Update();

	// 取得/設定
public:

	// 押された処理の設定
	void SetOnPushCommand(std::function<void()> onPushCommand)
	{
		m_onPushCommand = onPushCommand;
	}

	// ドラック中の処理の設定
	void SetOnDrugCommand(std::function<void()> onDrugCommand)
	{
		m_onDrugCommand = onDrugCommand;
	}

	// ホバー時の処理の設定
	void SetOnHoverEnterCommand(std::function<void()> onHoverEnterCommand)
	{
		m_onHoverEnterCommand = onHoverEnterCommand;
	}

	// ホバー中の処理の設定
	void SetOnHoverStayCommand(std::function<void()> onHoverStayCommand)
	{
		m_onHoverStayCommand = onHoverStayCommand;
	}

	// ホバー離脱時の処理の設定
	void SetOnHoverExitCommand(std::function<void()> onHoverExitCommand)
	{
		m_onHoverExitCommand = onHoverExitCommand;
	}

	void SetLayerDepth(float layerDepth)
	{
		m_spriteRenderer->SetLayerDepth(layerDepth);
		GetGameObject()->GetComponent<TextRenderer>()->SetLayerDepth(layerDepth + 0.1f);
	}

	// 内部実装
private:

};
