/*****************************************************************//**
 * \file   PlayerStateContext.h
 * \brief  プレイヤーステート用のコンテキスト
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Physics/RigidBody.h"
#include "Game/Component/Default/Physics/Transform.h"
#include "Game/Component/Ball/BallController.h"
#include "Game/Component/Player/PlayerStatusController.h"
#include "Game/Component/Player/PlayerController.h"

struct PlayerStateContext
{
	Rigidbody* rigitbody;
	Transform* transform;
	BallController* ballController;
	PlayerStatusController* playerStatusController;
	PlayerController* playerController;
};
