/*****************************************************************//**
 * \file   OrthgraphicCamera.h
 * \brief  正投影カメラ
 * 
 * \author 深沢拓矢
 * \date   October 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"
#include "Game/Component/Camera/Camera.h"
#include "Game/Common/Screen.h"

/**
 * @brief 正投影カメラ
 */
class  OrthgraphicCamera : public Camera {

	// メンバ変数の宣言 -------------------------------------------------

	float m_width;		// 横幅
	float m_height;		// 縦幅

	// プロパティの設定
	BeginProperty()
		AddProperty(m_width,	PropertyType::Float)
		AddProperty(m_height,	PropertyType::Float)
		AddProperty(m_nearclip,		PropertyType::Float)
		AddProperty(m_farclip,		PropertyType::Float)
	EndProperty()

	// コンポーネント名の設定
	SetCompName("OrthgraphicCamera")

		// メンバ関数の宣言 -------------------------------------------------
		// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	OrthgraphicCamera(IGameObject* gameObject);

	// デストラクタ
	~OrthgraphicCamera() = default;

	// 操作
public:

	// ウィンドウサイズ依存のリソースの設定
	void SetWindowSizeResource() override
	{
		m_proj = DirectX::SimpleMath::Matrix::CreateOrthographic(
			m_width,
			m_height,
			m_nearclip,
			m_farclip);
	}

public:

	// WidthとHeightの設定
	void SetSize(const DirectX::SimpleMath::Vector2& size)
	{
		m_width = size.x;
		m_height = size.y;
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