/*****************************************************************//**
 * \file   Transform.h
 * \brief  トランスフォーム 
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

	DirectX::SimpleMath::Vector3 m_position;		// 位置

	DirectX::SimpleMath::Quaternion m_quaternion;	// 回転

	float m_scale = 1.0f;							// スケール

	Transform* m_parentTransform = nullptr;			// 親のトランスフォーム


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
	void Rotate(const DirectX::SimpleMath::Quaternion& quaternion);

	// 取得/設定
public:

	// ポジションの取得
	DirectX::SimpleMath::Vector3 GetPosition() const
	{
		if (m_parentTransform != nullptr)
		{
			return m_parentTransform->GetPosition() + m_position;
		}
		else return m_position;
	}

	// 回転の取得
	DirectX::SimpleMath::Quaternion GetQuaternion() const
	{
		if (m_parentTransform != nullptr)
		{
			return m_parentTransform->GetQuaternion() * m_quaternion;
		}
		else return m_quaternion;
	}

	// スケールの取得
	float GetScale() const
	{
		if (m_parentTransform != nullptr)
		{
			return m_parentTransform->GetScale() * m_scale;
		}
		else return m_scale;
	}

	// ワールド行列の取得
	DirectX::SimpleMath::Matrix GetWorld() const
	{
		// 拡大行列
		SimpleMath::Matrix scale
			= SimpleMath::Matrix::CreateScale(GetScale());
		// 回転行列
		SimpleMath::Matrix rotate
			= SimpleMath::Matrix::CreateFromQuaternion(GetQuaternion());
		// 移動行列
		SimpleMath::Matrix trans
			= SimpleMath::Matrix::CreateTranslation(GetPosition());

		// ワールド行列
		SimpleMath::Matrix world = scale * rotate * trans;

		if (m_parentTransform != nullptr)
		{
			return m_parentTransform->GetWorld() * world;
		}
		else return world;
	}

	// ポジションの設定
	void SetPosition(const DirectX::SimpleMath::Vector3& position)
	{
		m_position = position;
	}

	// 回転の設定
	void SetQuaternion(DirectX::SimpleMath::Quaternion quaternion)
	{
		m_quaternion = quaternion;
	}

	// スケールの設定
	void SetScale(float scale)
	{
		m_scale = scale;
	}

	// 親トランスフォームの設定
	void SetParent(Transform* parent)
	{
		m_parentTransform = parent;
		// ローカル座標にする
		m_position -= m_parentTransform->GetPosition();
	}

	// 内部実装
private:

};
