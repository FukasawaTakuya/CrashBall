/*****************************************************************//**
 * \file   Rigidbody.cpp
 * \brief  物理演算コンポーネントクラス
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#include "pch.h"
#include "RigidBody.h"
#include "Game/Engine/Time.h"

using namespace DirectX;

RegisterComponent(Rigidbody)

/**
 * \brief コンストラクタ
 *
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 */
Rigidbody::Rigidbody(IGameObject* gameObject)
	: Component(gameObject)
{
}

/**
 * \brief デストラクタ.
 * 
 */
Rigidbody::~Rigidbody()
{
}

/**
 * \brief 加速
 * 
 * \param accel 加速度
 */
void Rigidbody::Accel(DirectX::SimpleMath::Vector3 accel)
{
	m_accel += accel;
}

/**
 * \brief 加速度の適用
 * 
 */
void Rigidbody::ApplyAccel()
{
	m_velocity += m_accel * Time::GetElapsedTime();
}

/**
 * \brief 重力の適用
 * 
 */
void Rigidbody::ApplyGravity()
{
	m_velocity += m_gravityAcceleration * 
		SimpleMath::Vector3::Down * Time::GetElapsedTime();
}

/**
 * \brief 摩擦の適用
 * 
 */
void Rigidbody::ApplyFriction()
{
	m_velocity -= m_velocity * m_friction * Time::GetElapsedTime();
}