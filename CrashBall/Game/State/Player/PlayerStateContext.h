#pragma once

#include "Game/Component/Default/Rigidbody.h"
#include "Game/Component/Default/Transform.h"
#include "Game/Component/PlayerStatusController.h"
#include "Game/Component/PlayerController.h"

struct PlayerStateContext
{
	RigidBody* rigitbody;
	Transform* transform;
	BallController* ballController;
	PlayerStatusController* playerStatusController;
	PlayerController* playerController;
};
