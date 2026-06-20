#pragma once

#include "Game/Component/Default/Physics/RigidBody.h"
#include "Game/Component/Default/Physics/Transform.h"
#include "Game/Component/Player/PlayerStatusController.h"
#include "Game/Component/Player/PlayerController.h"

struct PlayerStateContext
{
	RigidBody* rigitbody;
	Transform* transform;
	BallController* ballController;
	PlayerStatusController* playerStatusController;
	PlayerController* playerController;
};
