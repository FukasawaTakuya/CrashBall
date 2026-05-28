/*****************************************************************//**
 * \file   Transform.cpp
 * \brief  トランスフォーム 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#include "pch.h"
#include "Transform.h"

/**
 * \brief コンストラクタ
 * 
 */
Transform::Transform(IGameObject* owner)
	: Component(owner)
{
}

/**
 * \brief デストラクタ
 * 
 */
Transform::~Transform()
{
}

/**
 * \brief 移動
 * 
 * \param trans 移動ベクトル
 */
void Transform::Translate(const DirectX::SimpleMath::Vector3& trans)
{
	m_position += trans;
}

/**
 * \brief 回転
 * 
 * \param quaternion クオータニオン
 */
void Transform::Rotate(const DirectX::SimpleMath::Quaternion& quaternion)
{
	m_quaternion *= quaternion;
}
