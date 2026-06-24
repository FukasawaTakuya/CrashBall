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
 * \param コンポーネントを所有するゲームオブジェクト
 */
Transform::Transform(IGameObject* gameObejct)
	: Component(gameObejct)
{
}

/**
 * \brief コピーコンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 * \param transform トランスフォームコンポーネント
 */
Transform::Transform(IGameObject* gameObject, const Transform& transform)
	: Component(gameObject)
	, m_position(transform.m_position)
	, m_rotate(transform.m_rotate)
	, m_scale(transform.m_scale)
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
 * \param rotate クオータニオン
 */
void Transform::Rotate(const DirectX::SimpleMath::Quaternion& rotate)
{
	m_rotate *= rotate;
}
