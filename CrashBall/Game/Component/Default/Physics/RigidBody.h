/*****************************************************************//**
 * \file   RigidBody.h
 * \brief  物理演算コンポーネントクラス
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "..\Component.h"

/**
 * \brief 物理演算コンポーネント
 */
class  Rigidbody : public Component {

	// インスペクター編集GUIをフレンド化
	friend class ObjectInspectorGui;

	// データメンバの宣言 -----------------------------------------------
private:

	DirectX::SimpleMath::Vector3 m_velocity;	// 速度

	DirectX::SimpleMath::Vector3 m_accel;		// 加速度

	float m_gravityAcceleration = 0.0f;			// 重力加速度

	float m_friction = 0.0f;					// 摩擦係数

	float m_mass = 1.0f;						// 質量

	bool m_isDynamic = 1.0f;					// 動的か

	// プロパティの設定
	BeginProperty()
		AddProperty(m_gravityAcceleration, PropertyType::Float)
		AddProperty(m_friction, PropertyType::Float)
		AddProperty(m_mass, PropertyType::Float)
		AddProperty(m_isDynamic, PropertyType::Bool)
	EndProperty()

	// コンポーネント名の設定
	SetCompName("Rigidbody")


	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// デフォルトコンストラクタ
	Rigidbody() = default;

	// コンストラクタ
	Rigidbody(
		IGameObject* gameObject, 
		float gravityAcceleration, 
		float friction);

	// コピーコンストラクタ
	Rigidbody(
		IGameObject* gameObject,
		const Rigidbody& other
	);

	// デストラクタ
	~Rigidbody();

	// 操作
public:

	// 加速
	void Accel(DirectX::SimpleMath::Vector3 accel);

	// 加速度の適用
	void ApplyAccel();

	// 重力の適用
	void ApplyGravity();

	// 摩擦
	void ApplyFriction();

	// 取得/設定
public:

	// 速度の取得
	DirectX::SimpleMath::Vector3 GetVelocity() const { return m_velocity; }

	// 速度の設定
	void SetVelocity(DirectX::SimpleMath::Vector3 velo) { m_velocity = velo; }

	// 速度の加算
	void AddVelocity(DirectX::SimpleMath::Vector3 velo) { m_velocity += velo; }

	// 加速度のリセット
	void ResetAccel() { m_accel = DirectX::SimpleMath::Vector3::Zero; }

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

	// JsonConvert
private:
	friend void to_json(nlohmann::json& j, const Rigidbody& transfrom);
	friend void from_json(const nlohmann::json& j, Rigidbody& rigidbody);
};
