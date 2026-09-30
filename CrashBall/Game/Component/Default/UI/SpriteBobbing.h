/*****************************************************************//**
 * \file   SpriteBobbing.h
 * \brief  スプライトを浮遊させるコンポーネント
 * 
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"
#include "Game/Component/Default/Physics/RectTransform.h"


/**
 * @brief スプライトを浮遊させるコンポーネント
 */
class  SpriteBobbing : public Component 
{
	// メンバ変数の宣言 -----------------------------------------------
private:

	float						 m_radian;					// sin波に使う角度
	RectTransform*				 m_rectTransform = nullptr;	// トランスフォームのキャッシュ

	float						 m_amplitude;	// 揺れの大きさ
	float						 m_frequency;	// 揺れの速さ(元の位置に戻るまでの秒数)
	DirectX::SimpleMath::Vector2 m_initPos;		// 初期位置

	// プロパティの設定
	BeginProperty()
		AddProperty(m_amplitude, PropertyType::Float)
		AddProperty(m_frequency, PropertyType::Float)
		AddProperty(m_initPos, PropertyType::Vector2)
	EndProperty()

	// コンポーネント名の設定
	SetCompName("SpriteBobbing")

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	SpriteBobbing(IGameObject* gameObject);

	// デストラクタ
	~SpriteBobbing() = default;

	// 操作
public:

	// 更新
	void Update(const GameContext& gameContext);

	// 浮遊
	void Bobbing();

	// 取得/設定
public:

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

	// JsonConverter
private:
	friend void to_json(json& j, const SpriteBobbing& spriteBobbing);
	friend void from_json(const json& j, SpriteBobbing& spriteBobbing);

	// 演算子オーバーロード
public:

	void operator=(const SpriteBobbing& other)
	{
		m_amplitude = other.m_amplitude;
		m_frequency = other.m_frequency;
		m_initPos = other.m_initPos;
	}

};
