#pragma once

#include "Game/Component/Default/Component.h"
#include "Default/Renderer/TextRenderer.h"
#include "Default/Renderer/SpriteRenderer.h"

/**
 * @brief
 */
class  ResultPanel : public Component {

	float m_alpha = 0.0f;
	bool m_startResult = false;

	TextRenderer* m_resultText = nullptr;
	TextRenderer* m_buttonText = nullptr;
	SpriteRenderer* m_backGround = nullptr;

	// プロパティの設定
	BeginProperty()
		AddProperty(m_resultText, PropertyType::Component)
		AddProperty(m_buttonText, PropertyType::Component)
	EndProperty()

		// コンポーネント名の設定
	SetCompName("ResltPanel")

		// メンバ関数の宣言 -------------------------------------------------
		// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	ResultPanel(IGameObject* gameObject) : Component(gameObject) {}

	// デストラクタ
	~ResultPanel() = default;

	// 操作
public:

	// 更新
	virtual void Awake() override;

	// 更新
	virtual void Start(const GameContext& gameContext) override;

	// 更新
	virtual void Update(const GameContext& gameContext) override;

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