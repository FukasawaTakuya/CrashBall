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

	// メンバ変数の宣言 -----------------------------------------------
protected:

	std::function<void()> m_onPushCommand = [](){};			// 押されたときの処理
	std::function<void()> m_onDrugCommand = [](){};			// ドラック中の処理

	std::function<void()> m_onFocusEnterCommand = [](){};	// フォーカス時の処理
	std::function<void()> m_onFocusStayCommand  = [](){};	// フォーカス中の処理
	std::function<void()> m_onFocusExitCommand  = [](){};	// フォーカス離脱の処理

	bool m_isOnClick	= false;	// クリックされたか
	bool m_isOnRelease	= false;	// ボタンが離されたか
	bool m_isPush		= false;	// 押されたか

	bool m_isFocus		= false;	// フォーカス状態か
	bool m_prevIsFocus  = false;	// 前フレームのフォーカス状態

	// コンポーネントのキャッシュ
	RectTransform*  m_rectTransform  = nullptr;
	SpriteRenderer* m_spriteRenderer = nullptr;

	// プロパティの設定
	BeginProperty()
	EndProperty()

	// コンポーネント名の設定
	SetCompName("ButtonController")


	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	ButtonController(IGameObject* gameObject);

	// デストラクタ
	~ButtonController() = default;

	// 操作
public:

	// アタッチ時の処理
	virtual void Awake() override;

	// 開始処理
	virtual void Start(const GameContext& gameContext) override;

	// 更新
	virtual void Update(const GameContext& gameContext) override;

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

	// フォーカス時の処理の設定
	void SetOnFocusEnterCommand(std::function<void()> onFocusEnterCommand)
	{
		m_onFocusEnterCommand = onFocusEnterCommand;
	}

	// フォーカス中の処理の設定
	void SetOnFocusStayCommand(std::function<void()> onFocusStayCommand)
	{
		m_onFocusStayCommand = onFocusStayCommand;
	}

	// フォーカス離脱時の処理の設定
	void SetOnFocusExitCommand(std::function<void()> onFocusExitCommand)
	{
		m_onFocusExitCommand = onFocusExitCommand;
	}

	// 描画順の設定
	void SetLayerDepth(float layerDepth)
	{
		m_spriteRenderer->SetLayerDepth(layerDepth);
		GetGameObject()->GetComponent<TextRenderer>()->SetLayerDepth(layerDepth + 0.001f);
	}

	// 内部実装
private:

	// プロパティの取得
	const std::vector<PropertyInfo>& GetProperties() const override
	{
		return m_properties;
	}

	// コンポーネント名の取得
	std::string GetCompName() const override
	{
		return m_compName;
	}

};
