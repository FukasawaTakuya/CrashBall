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

	DirectX::SimpleMath::Vector2 m_localPosition;	// 位置

	float m_localRotate = 0.0f;						// 回転

	DirectX::SimpleMath::Vector2 m_localScale
		= DirectX::SimpleMath::Vector2::One;	// スケール

	Origin m_origin = Origin::Center;			// 基準位置

	RectTransform* m_parent = nullptr;	// 親のトランスフォーム

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// デフォルトコンストラクタ
	RectTransform() = default;

	// コンストラクタ
	RectTransform(IGameObject* gameObject);

	// コピーコンストラクタ
	RectTransform(
		IGameObject* gameObject, 
		const RectTransform& other);

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

	// ワールド座標の取得
	DirectX::SimpleMath::Vector2 GetWorldPosition() const
	{
		if (m_parent != nullptr)
		{
			return m_localPosition + m_parent->GetWorldPosition();
		}
		else
		{
			return m_localPosition;
		}
	}

	// ワールド回転の取得
	float GetWorldRotate() const
	{
		if (m_parent != nullptr)
		{
			return m_localRotate + m_parent->GetWorldRotate();
		}
		else
		{
			return m_localRotate;
		}
	}

	// ワールドスケールの取得
	DirectX::SimpleMath::Vector2 GetWorldScale() const
	{
		if (m_parent != nullptr)
		{
			return m_localScale * m_parent->GetWorldScale();
		}
		else
		{
			return m_localScale;
		}
	}

	// ローカル座標の取得
	DirectX::SimpleMath::Vector2 GetLocalPosition() const
	{
		return m_localPosition;
	}

	// ローカル回転の取得
	float GetLocalRotate() const
	{
		return m_localRotate;
	}

	// ローカルスケールの取得
	DirectX::SimpleMath::Vector2 GetLocalScale() const
	{
		return m_localScale;
	}

	// 基準位置の取得
	DirectX::SimpleMath::Vector2 GetOrigin(float width, float height) const
	{
		DirectX::SimpleMath::Vector2 offset = originOffeset[static_cast<int>(m_origin)];

		return DirectX::SimpleMath::Vector2(offset.x * width, offset.y * height);
	}

	// 左端のX座標の取得(World)
	float GetLeft(float width) const
	{
		DirectX::SimpleMath::Vector2 offset = originOffeset[static_cast<int>(m_origin)];

		float leftPos = m_localPosition.x - width * offset.x;

		return leftPos;
	}

	// 右端のX座標の取得(World)
	float GetRight(float width) const
	{
		DirectX::SimpleMath::Vector2 offset = originOffeset[static_cast<int>(m_origin)];

		float rightPos = m_localPosition.x + width * (1.0f - offset.x);

		return rightPos;
	}

	// 上端のY座標の取得(World)
	float GetTop(float height) const
	{
		DirectX::SimpleMath::Vector2 offset = originOffeset[static_cast<int>(m_origin)];

		float toptPos = m_localPosition.y - height * offset.y;

		return toptPos;
	}

	// 下端のY座標の取得(World)
	float GetBottom(float height) const
	{
		DirectX::SimpleMath::Vector2 offset = originOffeset[static_cast<int>(m_origin)];

		float bottomtPos = m_localPosition.y + height * (1.0f - offset.y);

		return bottomtPos;
	}


	// ワールド座標の設定
	void SetWorldPosition(const DirectX::SimpleMath::Vector2& position)
	{
		m_localPosition = position;
	}

	// ローカル座標の設定
	void SetLocalPosition(const DirectX::SimpleMath::Vector2& position)
	{
		m_localPosition = position;
	}

	// ローカル回転の設定
	void SetLocalRotate(float rotate)
	{
		m_localRotate = rotate;
	}

	// ローカルスケールの設定
	void SetLocalScale(const DirectX::SimpleMath::Vector2& scale)
	{
		m_localScale = scale;
	}

	// ローカルスケールの設定
	void SetLocalScale(float x, float y)
	{
		m_localScale.x = x;
		m_localScale.y = y;
	}

	// ローカルスケールの設定
	void SetLocalScale(float scale)
	{
		m_localScale = DirectX::SimpleMath::Vector2::One * scale;
	}

	// 基準位置の設定
	void SetOrigin(Origin origin)
	{
		m_origin = origin;
	}

	// 親の設定
	void SetParent(RectTransform* parent)
	{
		m_parent = parent;
	}

	// 内部実装
private:

	// JsonConvert
private:
	friend void to_json(json& j, const RectTransform& rectTransfrom);
	friend void from_json(const json& j, RectTransform& triangle);

	// 演算子オーバーロード
public:

	void operator=(const RectTransform& other)
	{
		m_localPosition = other.m_localPosition;
		m_localRotate = other.m_localRotate;
		m_localScale = other.m_localScale;
		m_origin = other.m_origin;
	}
};
