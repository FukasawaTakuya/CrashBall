/*****************************************************************//**
 * \file   Transform.cpp
 * \brief  トランスフォーム 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#include "pch.h"
#include "Transform.h"

RegisterComponent(Transform)

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
	m_localPosition += trans;
	m_isDirty = true;
}

/**
 * \brief 回転
 * 
 * \param rotate クオータニオン
 */
void Transform::Rotate(const DirectX::SimpleMath::Quaternion& rotate)
{
	m_localRotate *= rotate;
	m_isDirty = true;
}
