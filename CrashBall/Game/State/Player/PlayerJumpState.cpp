#include "pch.h"
#include "PlayerJumpState.h"
#include "Game/GameObject/Player/Player.h"
#include "Game/Common/InputSystem.h"
#include "PlayerMoveState.h"

PlayerJumpState::PlayerJumpState()
{
}

PlayerJumpState::~PlayerJumpState()
{
}

/**
 * \brief 初期化処理
 * 
 */
void PlayerJumpState::Initialize()
{
}

void PlayerJumpState::OnEnter()
{
}

void PlayerJumpState::Update()
{
    // 物理演算コンポーネントの取得
    RigidBody* rigidbody = m_owner->GetComponent<RigidBody>();

    auto key = Keyboard::Get().GetState();

    if (key.Space) m_pStateMachine->ChangeState<PlayerMoveState>();
}

void PlayerJumpState::OnExit()
{
}
