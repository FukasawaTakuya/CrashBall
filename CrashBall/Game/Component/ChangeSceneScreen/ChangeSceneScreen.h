/*****************************************************************//**
 * \file   ChangeSceneScreen.h
 * \brief  シーン変更スクリーン
 * 
 * \author 深沢拓矢
 * \date   September 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"
#include "Game/Component/Default/Renderer/SpriteRenderer.h"
#include "Game/Common/Easing.h"

/**
 * @brief シーン変更スクリーン
 */
class  ChangeSceneScreen : public Component {

	// メンバ変数の宣言 -------------------------------------------------
protected:
	// コンポーネントのキャッシュ
	SpriteRenderer* m_spriteRenderer;

	bool m_isIn;	// シーンインフラグ
	bool m_isOut;	// シーンアウトフラグ

	std::string m_nextScene;	// 遷移するシーン名
	float m_changeTime;			// 遷移時間

private:
	// プロパティの設定
	BeginProperty()
		AddProperty(m_nextScene, PropertyType::String)
		AddProperty(m_changeTime, PropertyType::Float)
	EndProperty()

		// コンポーネント名の設定
	SetCompName("ChangeSceneScreen")

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	ChangeSceneScreen(IGameObject* gameObject);

	// デストラクタ
	~ChangeSceneScreen() = default;

	// 操作
public:

	// アタッチ時の処理
	void Awake();

	// 開始処理
	void Start(const GameContext& gameContext) override;

	// シーンに入る
	virtual void SceneIn() = 0;

	// シーンから出る
	virtual void SceneOut() = 0;

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