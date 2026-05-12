/*****************************************************************//**
 * \file   RigidBody.cpp
 * \brief  物理挙動に関するソースファイル
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "RigidBody.h"
#include "Game/Common/TimeManager.h"

using namespace DirectX;

// メンバ関数の定義 ===================================================

/**
 * \brief コンストラクタ
 * 
 * \param 摩擦係数
 */
RigidBody::RigidBody(float gravity, float friction)
	: m_gravity{ gravity }
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
	m_velocity += m_accel * TimeManager::Instance().GetElapsedTime();
}

/**
 * \brief 重力の適用
 * 
 */
void RigidBody::ApplyGravity()
{
	m_velocity += m_gravity * SimpleMath::Vector3::Down * TimeManager::Instance().GetElapsedTime();
}

/**
 * \brief 摩擦の適用
 * 
 */
void RigidBody::ApplyFriction()
{
	m_velocity *= m_friction;
}
