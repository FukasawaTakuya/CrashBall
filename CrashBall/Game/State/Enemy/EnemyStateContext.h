#pragma once

#include "Game/Component/Transform.h"
#include "Game/Component/Rigidbody.h"


struct EnemyStateContext
{
	Transform* trasnform;
	RigidBody* rigidbody;
};
