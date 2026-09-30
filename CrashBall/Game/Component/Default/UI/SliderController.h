/*****************************************************************//**
 * \file   SliderController.h
 * \brief  スライダー操作コンポーネント
 * 
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"
#include "Game/Component/Default/Renderer/SpriteRenderer.h"


/**
 * @brief スライダー操作コンポーネント
 */
class  SliderController : public Component 
{
	// メンバ変数の宣言 -----------------------------------------------
private:

	float m_targetAmount;	// 目標値

	SpriteRenderer* m_spriteRenderer = nullptr;	// コンポーネントのキャッシュ

	float m_slideSpeed;	// スライド速度

	// プロパティの設定
	BeginProperty()
		AddProperty(m_slideSpeed, PropertyType::Float)
	EndProperty()

	// コンポーネント名の設定
	SetCompName("SliderController")


	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	SliderController(IGameObject* gameObject);

	// デストラクタ
	~SliderController() = default;

	// 更新 
	void Slide();

	// 操作
public:

	// アタッチ時の処理
	void Awake();

	// 取得/設定
public:

	// 目標値の設定
	void SetTargetAmount(float targetAmount)
	{
		m_targetAmount = std::clamp(targetAmount, 0.0f, 1.0f);
	}

	// 現在値の設定
	void SetCurrentAmount(float currentAmount)
	{
		m_spriteRenderer->SetFillAmount(currentAmount);
	}


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
