#pragma once

#include "Game/Component/Default/Component.h"
#include "Game/Component/Camera/Camera.h"
#include "Game/Common/Screen.h"

/**
 * @brief サブカメラ
 */
class  OrthgraphicCamera : public Camera {

	// メンバ変数の宣言 -------------------------------------------------

	float m_widthView;		// 横幅
	float m_heightView;		// 縦幅

	// プロパティの設定
	BeginProperty()
		AddProperty(m_widthView,	PropertyType::Float)
		AddProperty(m_heightView,	PropertyType::Float)
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
			m_widthView,
			m_heightView,
			m_nearclip,
			m_farclip
		);
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