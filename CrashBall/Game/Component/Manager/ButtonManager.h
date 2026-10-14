/*****************************************************************//**
 * \file   ButtonManager.h
 * \brief  
 * 
 * \author 深沢拓矢
 * \date   October 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"
#include "Game/Component/Default/UI/ButtonController.h"

/**
 * @brief
 */
class  ButtonManager : public Component {

	// メンバ変数の宣言 -------------------------------------------------

	// 初期ボタン
	ButtonController* m_firstButton = nullptr;

	// 現在ボタン
	ButtonController* m_currentButton = nullptr;

	// 移動先ボタン
	ButtonController* m_nextButton = nullptr;



	// プロパティの設定
	BeginProperty()
		AddProperty(m_firstButton, PropertyType::Component)
	EndProperty()

	// コンポーネント名の設定
	SetCompName("ButtonManager")

		// メンバ関数の宣言 -------------------------------------------------
		// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	ButtonManager(IGameObject* gameObject);

	// デストラクタ
	~ButtonManager() = default;

	// 操作
public:

	// アタッチ時の処理
	void Awake() override;
	// 開始処理
	void Start(const GameContext& gameContext) override;
	// 更新
	void Update(const GameContext& gameContext) override;

	// 内部実装
private:

	// プロパティの取得
	virtual const std::vector<PropertyInfo>& GetProperties() const override
	{
		return m_properties;
	}

	// コンポーネント名の取得
	virtual std::string GetCompName() const override
	{
		return m_compName;
	}
};