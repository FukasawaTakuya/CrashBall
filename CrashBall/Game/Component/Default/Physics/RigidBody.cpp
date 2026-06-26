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

/**
 * \brief コンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 * \param gravityAcceleration 重力加速度
 * \param friction 摩擦係数
 */
Rigidbody::Rigidbody(
	IGameObject* gameObject,
	float		 gravityAcceleration, 
	float		 friction)
	: Component				(gameObject)
	, m_gravityAcceleration	(gravityAcceleration)
	, m_friction			(friction)
{
}

/**
 * \brief コピーコンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 * \param rigidbody 物理演算コンポーネント
 */
Rigidbody::Rigidbody(
	IGameObject*	 gameObject, 
	const Rigidbody& rigidbody)
	: Component				(gameObject)
	, m_gravityAcceleration	(rigidbody.m_gravityAcceleration)
	, m_friction			(rigidbody.m_friction)
	, m_mass				(rigidbody.m_mass)
	, m_isDynamic			(rigidbody.m_isDynamic)
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