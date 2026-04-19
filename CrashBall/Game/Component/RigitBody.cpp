/*****************************************************************//**
 * \file   RigitBody.cpp
 * \brief  物理挙動に関するソースファイル
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#include "pch.h"
#include "RigitBody.h"

/**
 * \brief	コンストラクタ.
 * 
 * \param	摩擦係数
 */
RigitBody::RigitBody(float gravity, float friction)
	: m_gravity{ gravity }
	, m_friction{ friction }
{
}

/**
 * \brief	デストラクタ.
 * 
 */
RigitBody::~RigitBody()
{
}

/**
 * \brief	加速.
 * 
 * \param	加速度
 */
void RigitBody::Accel(DirectX::SimpleMath::Vector3 accel)
{
	m_accel += accel;
}

void RigitBody::ApplyAccel()
{
	m_velocity += m_accel/* * elapsedTime*/;
}

/**
 * \brief	重力の適用.
 * 
 */
void RigitBody::ApplyGravity()
{
	m_accel *= m_gravity;/* *elapsedTime*/
}

/**
 * \brief	摩擦の適用.
 * 
 */
void RigitBody::ApplyFriction()
{
	m_velocity *= m_friction;
}
