/*****************************************************************//**
 * \file   RigidBody.cpp
 * \brief  物理挙動に関するソースファイル
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#include "pch.h"
#include "RigidBody.h"
#include "Game/ServiceLocator/TimeService.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 * \param 重力加速度
 * \param 摩擦係数
 */
RigidBody::RigidBody(
	float gravityAcceleration, 
	float friction)
	: m_gravityAcceleration{ gravityAcceleration }
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

void RigidBody::ApplyAccel()
{
	m_velocity += m_accel * TimeService::Instance().GetTime()->GetElapsedTime();
}

/**
 * \brief 重力の適用
 * 
 */
void RigidBody::ApplyGravity()
{
	m_velocity += m_gravityAcceleration * SimpleMath::Vector3::Down * TimeService::Instance().GetTime()->GetElapsedTime();
}

/**
 * \brief 摩擦の適用
 * 
 */
void RigidBody::ApplyFriction()
{
	m_velocity *= m_friction;
}
