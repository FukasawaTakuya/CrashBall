/*****************************************************************//**
 * \file   Sphere.cpp
 * \brief  球コライダー
 *
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/


#include "pch.h"
#include "Sphere.h"

/**
 * \brief コンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 * \param radius 半径
 */
Sphere::Sphere(IGameObject* gameObject, float radius)
	: Collider(gameObject, ColliderType::Sphere)
	, m_radius{ radius }
{
}

/**
 * \brief デストラクタ
 * 
 */
Sphere::~Sphere()
{
}
