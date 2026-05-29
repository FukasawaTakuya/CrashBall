#pragma once

#include "Game/Component/Rigidbody.h"
#include "Game/Component/Transform.h"
#include "Game/Component/PlayerController.h"

struct PlayerStateContext
{
	RigidBody* rigitbody;
	Transform* transform;
	PlayerController* playerController;
};
