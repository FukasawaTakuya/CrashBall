/*****************************************************************//**
 * \file   Transform.h
 * \brief  トランスフォーム 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"

/**
 * @brief トランスフォーム
 */
class  Transform : public Component 
{

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	DirectX::SimpleMath::Vector3 m_localPosition;		// 位置

	DirectX::SimpleMath::Quaternion m_localRotate;		// 回転

	DirectX::SimpleMath::Vector3 m_localScale 
		= DirectX::SimpleMath::Vector3::One;		// スケール

	Transform* m_parent = nullptr;	// 親のトランスフォーム

	mutable bool m_isDirty = true;

	mutable DirectX::SimpleMath::Matrix m_world;// ワールド行列

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// デフォルトコンストラクタ
	Transform() = default;

	// コンストラクタ
	Transform(IGameObject* gameObject);

	// コピーコンストラクタ
	Transform(
		IGameObject* gameObject,
		const Transform& other);

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

	// ワールド座標の取得
	DirectX::SimpleMath::Vector3 GetWorldPosition() const
	{
		if (m_parent != nullptr)
		{
			return m_localPosition + m_parent->GetWorldPosition();
		}
		return m_localPosition;
	}

	// ワールド回転の取得
	DirectX::SimpleMath::Quaternion GetWorldRotate() const
	{
		if (m_parent != nullptr)
		{
			return m_parent->GetWorldRotate() * m_localRotate;
		}
		return m_localRotate;
	}

	// ワールドスケールの取得
	DirectX::SimpleMath::Vector3 GetWorldScale() const
	{
		if (m_parent != nullptr)
		{
			return m_localScale + m_parent->GetWorldScale();
		}
		return m_localScale;
	}

	// ローカル座標の取得
	DirectX::SimpleMath::Vector3 GetLocalPosition() const
	{
		return m_localPosition;
	}

	// ローカル回転の取得
	DirectX::SimpleMath::Quaternion GetLocalRotate() const
	{
		return m_localRotate;
	}

	// ローカルスケールの取得
	DirectX::SimpleMath::Vector3 GetLocalScale() const
	{
		return m_localScale;
	}

	// 最大のスケールを取得
	float GetMaxScale() const
	{
		return std::max(std::max(m_localScale.x, m_localScale.y), m_localScale.z);
	}

	// ワールド行列の取得
	DirectX::SimpleMath::Matrix GetWorld() const
	{
		if (m_isDirty)
		{
			// 拡大行列
			DirectX::SimpleMath::Matrix scale
				= DirectX::SimpleMath::Matrix::CreateScale(GetWorldScale());
			// 回転行列
			DirectX::SimpleMath::Matrix rotate
				= DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetWorldRotate());
			// 移動行列
			DirectX::SimpleMath::Matrix trans
				= DirectX::SimpleMath::Matrix::CreateTranslation(GetWorldPosition());

			// ワールド行列
			m_world = (scale * rotate * trans);

			m_isDirty = false;
		}

		return m_world;
	}

	// ポジションの設定
	void SetPosition(const DirectX::SimpleMath::Vector3& position)
	{
		m_localPosition = position;
		m_isDirty = true;
	}

	// 回転の設定
	void SetQuaternion(DirectX::SimpleMath::Quaternion quaternion)
	{
		m_localRotate = quaternion;
		m_isDirty = true;
	}

	// スケールの設定
	void SetScale(const DirectX::SimpleMath::Vector3& scale)
	{
		m_localScale = scale;
		m_isDirty = true;
	}

	// スケールの設定
	void SetScale(float x, float y, float z)
	{
		m_localScale.x = x;
		m_localScale.y = y;
		m_localScale.z = z;
		m_isDirty = true;
	}

	// スケールの設定
	void SetScale(float scale)
	{
		m_localScale = DirectX::SimpleMath::Vector3::One * scale;
		m_isDirty = true;
	}

	// 内部実装
private:

	// JsonConvert
private:
	friend void from_json(const json& j, Transform& transform);
	friend void to_json(json& j, const Transform& transfrom);

public:

	void operator=(const Transform& other)
	{
		m_localPosition = other.m_localPosition;
		m_localRotate = other.m_localRotate;
		m_localScale = other.m_localScale;
	}
};
