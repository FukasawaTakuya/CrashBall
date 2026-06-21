/*****************************************************************//**
 * \file   Transform.h
 * \brief  トランスフォーム 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"

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

	DirectX::SimpleMath::Vector3 m_position;		// 位置

	DirectX::SimpleMath::Quaternion m_rotate;		// 回転

	float m_scale = 1.0f;							// スケール


	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Transform(IGameObject* owner);

	// デストラクタ
	~Transform();

	// 操作
public:

	// 移動
	void Translate(const DirectX::SimpleMath::Vector3& trans);

	// 回転
	void Rotate(const DirectX::SimpleMath::Quaternion& rotate);

	// 取得/設定
public:

	// ポジションの取得
	DirectX::SimpleMath::Vector3 GetPosition() const
	{
		return m_position;
	}

	// 回転の取得
	DirectX::SimpleMath::Quaternion GetRotate() const
	{
		return m_rotate;
	}

	// スケールの取得
	float GetScale() const
	{
		return m_scale;
	}

	// ワールド行列の取得
	DirectX::SimpleMath::Matrix GetWorld() const
	{
		// 拡大行列
		SimpleMath::Matrix scale
			= SimpleMath::Matrix::CreateScale(GetScale());
		// 回転行列
		SimpleMath::Matrix rotate
			= SimpleMath::Matrix::CreateFromQuaternion(GetRotate());
		// 移動行列
		SimpleMath::Matrix trans
			= SimpleMath::Matrix::CreateTranslation(GetPosition());

		// ワールド行列
		SimpleMath::Matrix world = scale * rotate * trans;

		return world;
	}

	// ポジションの設定
	void SetPosition(const DirectX::SimpleMath::Vector3& position)
	{
		m_position = position;
	}

	// 回転の設定
	void SetQuaternion(DirectX::SimpleMath::Quaternion quaternion)
	{
		m_rotate = quaternion;
	}

	// スケールの設定
	void SetScale(float scale)
	{
		m_scale = scale;
	}

	// 内部実装
private:

};
