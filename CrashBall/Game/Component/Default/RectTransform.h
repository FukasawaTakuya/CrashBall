/*****************************************************************//**
 * \file   RectTransform.h
 * \brief  2Dのトランスフォームコンポーネント
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"

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

	// 内部実装
private:

};
