/*****************************************************************//**
 * \file   Transform.cpp
 * \brief  トランスフォームに関するソースファイル
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#include "pch.h"
#include "Transform.h"

/**
 * \brief コンストラクタ.
 * 
 */
Transform::Transform()
{
}

/**
 * \brief デストラクタ.
 * 
 */
Transform::~Transform()
{
}

/**
 * \brief 移動.
 * 
 * \param trans
 */
void Transform::Translate(DirectX::SimpleMath::Vector3 trans)
{
	m_position += trans;
}

/**
 * \brief 回転.
 * 
 * \param rotate
 */
void Transform::Rotate(DirectX::SimpleMath::Matrix rotate)
{
	m_rotate *= rotate;
}

/**
 * \brief クオータニオンによる回転.
 * 
 * \param quaternion
 */
void Transform::RotateQuaternion(
	const DirectX::SimpleMath::Quaternion& quaternion)
{
	m_quaternion *= quaternion;
}

