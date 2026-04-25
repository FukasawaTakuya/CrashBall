#include "pch.h"
#include "PlayerJumpState.h"
#include "Game/GameObject/Player/Player.h"
#include "Game/Common/InputSystem.h"

PlayerJumpState::PlayerJumpState()
{
}

PlayerJumpState::~PlayerJumpState()
{
}

void PlayerJumpState::OnEnter()
{
}

void PlayerJumpState::Update()
{
    // 物理演算コンポーネントの取得
    RigitBody* rigidbody = m_owner->GetComponent<RigitBody>();
}

void PlayerJumpState::OnExit()
{
}
