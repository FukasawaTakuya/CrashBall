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
 * \brief コンストラクタ
 * 
 */
Transform::Transform()
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
 * \param rotate 回転行列
 */
void Transform::Rotate(DirectX::SimpleMath::Matrix rotate)
{
	m_rotate *= rotate;
}
