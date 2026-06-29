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
