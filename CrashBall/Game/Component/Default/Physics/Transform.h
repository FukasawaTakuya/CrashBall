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
	// メンバ変数の宣言 -----------------------------------------------
private:

	DirectX::SimpleMath::Vector3 m_localPosition;		// 位置
	DirectX::SimpleMath::Quaternion m_localRotate;		// 回転
	DirectX::SimpleMath::Vector3 m_localScale 
		= DirectX::SimpleMath::Vector3::One;		// スケール

	Transform* m_parent = nullptr;	// 親のトランスフォーム

	mutable bool m_isDirty = true;	// 変更フラグ

	mutable DirectX::SimpleMath::Matrix m_world;// ワールド行列

	// プロパティの設定
	BeginProperty()
		AddProperty(m_localPosition, PropertyType::Vector3)
		AddProperty(m_localRotate, PropertyType::Quaternion)
		AddProperty(m_localScale, PropertyType::Vector3)
	EndProperty()

	// コンポーネント名の設定
	SetCompName("Transform")

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Transform(IGameObject* gameObject);

	// デストラクタ
	~Transform() = default;

	// 操作
public:

	// 開始処理
	void Start(const GameContext& gameContext) override;

	// 更新
	void Update(const GameContext& gameContext) override;

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
			return m_localScale * m_parent->GetWorldScale();
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

	// 変更フラグの取得
	bool GetIsDirty() const
	{
		return m_isDirty;
	}

	// ワールド行列の取得
	DirectX::SimpleMath::Matrix GetWorld() const
	{
		// 変更があればワールド行列を更新
		if (m_isDirty)
		{
			UpdateWarldMat();
			m_isDirty = false;
		}

		return m_world;
	}

	// ワールド座標の設定
	void SetWorldPosition(const DirectX::SimpleMath::Vector3& position)
	{
		if (m_parent != nullptr)
		{
			m_localPosition = position - m_parent->GetWorldPosition();
		}
		else
		{
			m_localPosition = position;
		}
		m_isDirty = true;
	}

	// ローカル座標の設定
	void SetLocalPosition(const DirectX::SimpleMath::Vector3& position)
	{
		m_localPosition = position;
		m_isDirty = true;
	}

	// 回転の設定
	void SetRotate(DirectX::SimpleMath::Quaternion quaternion)
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

	// 実行中の親の設定
	void SetParentInRunTime(Transform* parent)
	{
		m_parent = parent;
		if (parent != nullptr)
		{
			m_localPosition -= parent->GetWorldPosition();
			DirectX::SimpleMath::Quaternion inverseRotate;
			parent->GetWorldRotate().Inverse(inverseRotate);
			m_localRotate *= inverseRotate;
			m_localScale = m_localScale / parent->GetWorldScale();
		}
	}

	// ビルド時の親の設定
	void SetParentInBuildTime(Transform* parent)
	{
		m_parent = parent;
	}

	// 内部実装
private:

	// 変更されたとき実行する関数
	void EditedFunc() override
	{
		Translate(DirectX::SimpleMath::Vector3::Zero);
	}

	// プロパティの取得
	const std::vector<PropertyInfo>& GetProperties() const override
	{
		return m_properties;
	}

	// コンポーネント名の取得
	std::string GetCompName() const override
	{
		return m_compName;
	}

	// ワールド行列の更新 GetWorld内で使うためconst
	void UpdateWarldMat() const;

};
