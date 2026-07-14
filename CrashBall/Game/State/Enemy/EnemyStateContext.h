/*****************************************************************//**
 * \file   EnemyStateContext.h
 * \brief  敵ステート用のコンテキスト
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Physics/Transform.h"
#include "Game/Component/Default/Physics/RigidBody.h"
#include "Game/Component/Enemy/EnemyController.h"

struct EnemyStateContext
{
	Transform* trasnform;
	Rigidbody* rigidbody;
	const EnemyController* enemyController;
};
