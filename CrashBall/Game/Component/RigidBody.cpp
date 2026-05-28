/*****************************************************************//**
 * \file   RigidBody.cpp
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
 * \param 重力加速度
 * \param 摩擦係数
 */
RigidBody::RigidBody(
	IGameObject* owner,
	float gravityAcceleration, 
	float friction)
	: Component(owner)
	, m_gravityAcceleration{ gravityAcceleration }
	, m_friction{ friction }
{
}

/**
 * \brief デストラクタ.
 * 
 */
RigidBody::~RigidBody()
{
}

/**
 * \brief 加速
 * 
 * \param 加速度
 */
void RigidBody::Accel(DirectX::SimpleMath::Vector3 accel)
{
	m_accel += accel;
}

/**
 * \brief 加速度の適用
 * 
 */
void RigidBody::ApplyAccel()
{
	m_velocity += m_accel * Time::GetElapsedTime();
}

/**
 * \brief 重力の適用
 * 
 */
void RigidBody::ApplyGravity()
{
	m_velocity += m_gravityAcceleration * 
		SimpleMath::Vector3::Down * Time::GetElapsedTime();
}

/**
 * \brief 摩擦の適用
 * 
 */
void RigidBody::ApplyFriction()
{
	//m_velocity *= m_friction;
	m_velocity *= exp(-1.25f * Time::GetElapsedTime());
}