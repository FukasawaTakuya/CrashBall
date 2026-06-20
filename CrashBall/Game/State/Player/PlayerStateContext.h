#pragma once

#include "Game/Component/Default/Physics/RigidBody.h"
#include "Game/Component/Default/Physics/Transform.h"
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
