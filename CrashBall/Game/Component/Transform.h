/*****************************************************************//**
 * \file   Transform.h
 * \brief  トランスフォームに関するヘッダーファイル
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "Component.h"

using namespace DirectX;

/**
 * @brief トランスフォーム
 */
class  Transform : public Component 
{

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	DirectX::SimpleMath::Vector3 m_position;	// 移動

	DirectX::SimpleMath::Matrix m_rotate;		// 回転

	float m_scale = 1.0f;						// スケール


	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Transform();

	// デストラクタ
	~Transform();

	// 操作
public:

	// 移動
	void Translate(const DirectX::SimpleMath::Vector3& trans);

	// 回転
	void Rotate(DirectX::SimpleMath::Matrix rotate);

	// 取得/設定
public:

	// ポジションの取得
	DirectX::SimpleMath::Vector3 GetPosition() const
	{
		return m_position;
	}

	// 回転の取得
	DirectX::SimpleMath::Matrix GetRotate() const
	{
		return m_rotate;
	}

	// スケールの取得
	float GetScale() const
	{
		return m_scale;
	}

	DirectX::SimpleMath::Matrix GetWorld() const
	{
		// 拡大行列
		SimpleMath::Matrix scale
			= SimpleMath::Matrix::CreateScale(m_scale);
		// 移動行列
		SimpleMath::Matrix trans
			= SimpleMath::Matrix::CreateTranslation(m_position);

		// ワールド行列
		SimpleMath::Matrix world = scale * m_rotate * trans;

		return world;
	}

	// ポジションの設定
	void SetPosition(const DirectX::SimpleMath::Vector3& position)
	{
		m_position = position;
	}

	// 回転の設定
	void SetRotate(DirectX::SimpleMath::Matrix rotate)
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
