/*****************************************************************//**
 * \file   TitleManager.h
 * \brief  タイトルマネージャ
 * 
 * \author 深沢拓矢
 * \date   September 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"
#include "Game/Component/ChangeSceneScreen/ChangeSceneScreen.h"

/**
 * @brief タイトルマネージャ
 */
class  TitleManager : public Component {

	// シーン遷移スクリーン
	ChangeSceneScreen* m_changeSceneScreen = nullptr;

	// プロパティの設定
	BeginProperty()
		AddProperty(m_changeSceneScreen, PropertyType::Component)
	EndProperty()

	// コンポーネント名の設定
	SetCompName("TitleManager")

		// メンバ関数の宣言 -------------------------------------------------
		// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	TitleManager(IGameObject* gameObject);

	// デストラクタ
	~TitleManager() = default;

	// 操作
public:

	// 更新
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