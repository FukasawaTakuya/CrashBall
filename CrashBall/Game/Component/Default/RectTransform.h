/*****************************************************************//**
 * \file   RectTransform.h
 * \brief  2Dのトランスフォームコンポーネント
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"

// 基準位置
enum class Origin
{
	Center = 0,
	LeftTop,
	LeftCenter,
	RightTop,
	RightCenter,
	OriginNum,
};

// 基準位置を決めるためのオフセット
const DirectX::SimpleMath::Vector2 originOffeset[static_cast<int>(Origin::OriginNum)]
{
	DirectX::SimpleMath::Vector2(0.5f, 0.5f),	// Center
	DirectX::SimpleMath::Vector2(0.0f, 0.0f),	// LeftTop
	DirectX::SimpleMath::Vector2(0.0f, 0.5f),	// LeftCenter
	DirectX::SimpleMath::Vector2(1.0f, 0.0f),	// RightTop
	DirectX::SimpleMath::Vector2(1.0f, 0.5f),	// RightCenter
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

	float m_rotate = 0.0f;		// 回転

	float m_scale = 1.0f;		// スケール

	Origin m_origin = Origin::Center;	// 基準位置

	RectTransform* m_parentTransfrom = nullptr;	// 親のトランスフォーム

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	RectTransform(IGameObject* gameObject);

	// デストラクタ
	~RectTransform();

	// 操作
public:

	// 移動
	void Translate(DirectX::SimpleMath::Vector2 trans);

	// 回転
	void Rotate(float rotate);

	// 取得/設定
public:

	// ポジションの取得
	DirectX::SimpleMath::Vector2 GetPosition() const
	{
		if (m_parentTransfrom != nullptr)
		{
			return m_parentTransfrom->GetPosition() + m_position;
		}
		else return m_position;
	}

	// 回転の取得
	float GetRotate() const
	{
		if (m_parentTransfrom != nullptr)
		{
			return m_parentTransfrom->GetRotate() + m_rotate;
		}
		else return m_rotate;
	}

	// スケールの取得
	float GetScale() const
	{
		if (m_parentTransfrom != nullptr)
		{
			return m_parentTransfrom->GetScale() * m_scale;
		}
		else return m_scale;
	}

	// 基準位置の取得
	DirectX::SimpleMath::Vector2 GetOrigin(float width, float height) const
	{
		DirectX::SimpleMath::Vector2 offset = originOffeset[static_cast<int>(m_origin)];

		return DirectX::SimpleMath::Vector2(offset.x * width, offset.y * height);
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
	void SetScale(float scale)
	{
		m_scale = scale;
	}

	// 基準位置の設定
	void SetOrigin(Origin origin)
	{
		m_origin = origin;
	}

	// 親のトランスフォームの設定
	void SetParent(RectTransform* parent)
	{
		m_parentTransfrom = parent;
		// ローカル座標にする
		m_position -= m_parentTransfrom->GetPosition();
	}

	// 内部実装
private:

};
