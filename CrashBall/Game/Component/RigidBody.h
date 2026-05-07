/*****************************************************************//**
 * \file   RigidBody.h
 * \brief  物理挙動に関するヘッダーファイル
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

// 多重インクルードの防止 =====================================================
#pragma once


// ヘッダファイルの読み込み ===================================================
#include "Component.h"

// クラスの前方宣言 ===================================================



// クラスの定義 ===============================================================
/**
 * @brief 基底オブジェクト
 */
class  RigidBody : public Component {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	DirectX::SimpleMath::Vector3 m_velocity;	// 速度

	DirectX::SimpleMath::Vector3 m_accel;		// 加速度

	float m_gravity;							// 重力

	float m_friction;							// 摩擦係数

	// TODO: 質量や反発係数

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	RigidBody(float gravity, float friction);

	// デストラクタ
	~RigidBody();

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

};
