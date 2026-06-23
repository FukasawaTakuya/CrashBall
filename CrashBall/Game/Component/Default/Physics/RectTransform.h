/*****************************************************************//**
 * \file   RectTransform.h
 * \brief  2Dのトランスフォームコンポーネント
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"

#include "nlohmann/json.hpp"

using namespace nlohmann;

// 基準位置
enum class Origin
{
	CenterTop = 0,
	Center,
	CenterBottom,
	LeftTop,
	LeftCenter,
	LeftBottom,
	RightTop,
	RightCenter,
	RightBottom,
	OriginNum,
};

// 基準位置を決めるためのオフセット
const DirectX::SimpleMath::Vector2 originOffeset[static_cast<int>(Origin::OriginNum)]
{
	DirectX::SimpleMath::Vector2(0.5f, 0.0f),	// CenterTop
	DirectX::SimpleMath::Vector2(0.5f, 0.5f),	// Center
	DirectX::SimpleMath::Vector2(0.5f, 1.0f),	// CenterBottom
	DirectX::SimpleMath::Vector2(0.0f, 0.0f),	// LeftTop
	DirectX::SimpleMath::Vector2(0.0f, 0.5f),	// LeftCenter
	DirectX::SimpleMath::Vector2(0.0f, 1.0f),	// LeftBottom
	DirectX::SimpleMath::Vector2(1.0f, 0.0f),	// RightTop
	DirectX::SimpleMath::Vector2(1.0f, 0.5f),	// RightCenter
	DirectX::SimpleMath::Vector2(1.0f, 1.0f),	// RightBottom
};

/**
 * @brief 2Dのトランスフォームコンポーネント
 */
class  RectTransform : public Component {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	DirectX::SimpleMath::Vector2 m_position;	// 位置

	float m_rotate = 0.0f;						// 回転

	DirectX::SimpleMath::Vector2 m_scale
		= DirectX::SimpleMath::Vector2::One;	// スケール

	Origin m_origin = Origin::Center;			// 基準位置

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	RectTransform(IGameObject* gameObject);

	// コピーコンストラクタ
	RectTransform(
		IGameObject* gameObject, 
		const RectTransform& rectTransform);

	// デストラクタ
	~RectTransform();

	// 操作
public:

	// 移動
	void Translate(const DirectX::SimpleMath::Vector2& trans);

	// 回転
	void Rotate(float rotate);

	// 取得/設定
public:

	// ポジションの取得
	DirectX::SimpleMath::Vector2 GetPosition() const
	{
		return m_position;
	}

	// 回転の取得
	float GetRotate() const
	{
		return m_rotate;
	}

	// スケールの取得
	DirectX::SimpleMath::Vector2 GetScale() const
	{
		return m_scale;
	}

	// 基準位置の取得
	DirectX::SimpleMath::Vector2 GetOrigin(float width, float height) const
	{
		DirectX::SimpleMath::Vector2 offset = originOffeset[static_cast<int>(m_origin)];

		return DirectX::SimpleMath::Vector2(offset.x * width, offset.y * height);
	}

	// 左端のX座標の取得
	float GetLeft(float width) const
	{
		DirectX::SimpleMath::Vector2 offset = originOffeset[static_cast<int>(m_origin)];

		float leftPos = m_position.x - width * offset.x;

		return leftPos;
	}

	// 右端のX座標の取得
	float GetRight(float width) const
	{
		DirectX::SimpleMath::Vector2 offset = originOffeset[static_cast<int>(m_origin)];

		float rightPos = m_position.x + width * (1.0f - offset.x);

		return rightPos;
	}

	// 上端のY座標の取得
	float GetTop(float height) const
	{
		DirectX::SimpleMath::Vector2 offset = originOffeset[static_cast<int>(m_origin)];

		float toptPos = m_position.y - height * offset.y;

		return toptPos;
	}

	// 下端のY座標の取得
	float GetBottom(float height) const
	{
		DirectX::SimpleMath::Vector2 offset = originOffeset[static_cast<int>(m_origin)];

		float bottomtPos = m_position.y + height * (1.0f - offset.y);

		return bottomtPos;
	}

	// ポジションの設定
	void SetPosition(const DirectX::SimpleMath::Vector2& position)
	{
		m_position = position;
	}

	// 回転の設定
	void SetRotate(float rotate)
	{
		m_rotate = rotate;
	}

	// スケールの設定
	void SetScale(const DirectX::SimpleMath::Vector2& scale)
	{
		m_scale = scale;
	}

	// スケールの設定
	void SetScale(float x, float y)
	{
		m_scale.x = x;
		m_scale.y = y;
	}

	// スケールの設定
	void SetScale(float scale)
	{
		m_scale = DirectX::SimpleMath::Vector2::One * scale;
	}

	// 基準位置の設定
	void SetOrigin(Origin origin)
	{
		m_origin = origin;
	}

	// 内部実装
private:

	// JsonConvert
private:
	friend void to_json(json& j, const RectTransform& rectTransfrom);
	friend void from_json(const json& j, RectTransform& triangle);
};
