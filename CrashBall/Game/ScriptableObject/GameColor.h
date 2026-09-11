#pragma once

#include "Game/Component/Default/Component.h"
#include "Game/Component/Default/ScriptableComponent.h"

/**
 * @brief 
 */
class  GameColor : public ScriptableComponent {

	// コンポーネント名の設定
	SetCompName("GameColor")

	// データメンバの宣言 -----------------------------------------------
public:

	DirectX::SimpleMath::Color m_playerColor;
	DirectX::SimpleMath::Color m_enemyColor;
	DirectX::SimpleMath::Color m_defaultFaceColor;
	DirectX::SimpleMath::Color m_attackGaugeColor;
	DirectX::SimpleMath::Color m_attackGaugeTrackColor;

private:
	BeginProperty()
		AddProperty(m_playerColor, PropertyType::Color)
		AddProperty(m_enemyColor, PropertyType::Color)
		AddProperty(m_defaultFaceColor, PropertyType::Color)
		AddProperty(m_attackGaugeColor, PropertyType::Color)
		AddProperty(m_attackGaugeTrackColor, PropertyType::Color)
	EndProperty()

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	GameColor(IGameObject* gameObject);

	// デストラクタ
	~GameColor() = default;

	// 操作
public:

	// 取得/設定
public:

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

	// 内部実装
private:

};
