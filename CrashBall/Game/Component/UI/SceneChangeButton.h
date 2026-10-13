/*****************************************************************//**
 * \file   SceneChangeButton.h
 * \brief  シーン変更ボタン
 * 
 * \author it252184
 * \date   October 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/UI/ButtonController.h"
#include "Game/Common/Easing.h"

/**
 * @brief シーン変更ボタン
 */
class  SceneChangeButton : public ButtonController {

	// メンバ変数の宣言 -------------------------------------------------

	std::string m_nextSceneName;		// 次シーン名

	Easing<DirectX::SimpleMath::Vector2> m_scale;	// スケールのイージング
	DirectX::SimpleMath::Vector2 m_defaultScale;	// デフォルトスケール
	float m_easeTime = 0.7f;						// イージングタイム

	// プロパティの設定
	BeginProperty()
		AddProperty(m_nextSceneName, PropertyType::String)
	EndProperty()

	// コンポーネント名の設定
	SetCompName("SceneChangeButton")

		// メンバ関数の宣言 -------------------------------------------------
		// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	SceneChangeButton(IGameObject* gameObject);

	// デストラクタ
	~SceneChangeButton() = default;

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