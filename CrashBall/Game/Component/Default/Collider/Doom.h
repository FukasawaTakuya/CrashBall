/*****************************************************************//**
 * \file   Doom.h
 * \brief  内側に押し出す球
 * 
 * \author 深沢拓矢
 * \date   September 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"
#include "Game/Component/Default/Collider/Collider.h"

/**
 * @brief
 */
class  Doom : public Collider {

	// メンバ変数の宣言 -------------------------------------------------
private:

	// 半径
	float m_radius;


	// プロパティの設定
	BeginProperty()
		AddProperty(m_radius, PropertyType::Float)
	EndProperty()

		// コンポーネント名の設定
	SetCompName("Doom")

		// メンバ関数の宣言 -------------------------------------------------
		// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Doom(IGameObject* gameObject);

	// デストラクタ
	~Doom() = default;

	// 操作
public:

	float GetRadius() const
	{
		return m_radius;
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