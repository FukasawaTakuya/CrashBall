/*****************************************************************//**
 * \file   Sphere.cpp
 * \brief  球コライダー
 *
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/


#include "pch.h"
#include "Sphere.h"

RegisterComponent(Sphere)

/**
 * \brief コンストラクタ
 *
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 */
Sphere::Sphere(
	IGameObject* gameObject)
	: Collider(gameObject, ColliderType::Sphere)
{
}


/**
 * \brief デストラクタ
 * 
 */
Sphere::~Sphere()
{
}

/**
 * \brief アタッチ時の処理
 * 
 */
void Sphere::Awake()
{
	Collider::Awake();
}
