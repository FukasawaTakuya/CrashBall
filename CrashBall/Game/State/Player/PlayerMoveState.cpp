#include "pch.h"
#include "PlayerMoveState.h"
#include "Game/GameObject/Player/Player.h"
#include "Game/Common/InputSystem.h"
#include "Game/Common/Camera.h"
#include "PlayerJumpState.h"

/**
 * \brief コンストラクタ.
 * 
 */
PlayerMoveState::PlayerMoveState()
{
}

/**
 * \brief デストラクタ.
 * 
 */
PlayerMoveState::~PlayerMoveState()
{
}

/**
 * \brief 開始処理.
 * 
 */
void PlayerMoveState::OnEnter()
{
}

/**
 * \brief 更新処理.
 * 
 */
void PlayerMoveState::Update()
{
    // キー情報の取得
    auto key = Keyboard::Get().GetState();
    // 物理演算コンポーネントの取得
    RigidBody* rigidbody = m_owner->GetComponent<RigidBody>();

    // 加速度のリセット
    rigidbody->ResetAccel();

    // 地上にいる場合
    if (m_owner->GetIsGround())
    {
        if (key.D) {
            rigidbody->Accel(m_owner->GetCamera()->GetRight() * 35.0f);
        }
        if (key.A) {
            rigidbody->Accel(-m_owner->GetCamera()->GetRight() * 35.0f);
        }
        if (key.W) {
            rigidbody->Accel(m_owner->GetCamera()->GetForward() * 35.0f);
        }
        if (key.S) {
            rigidbody->Accel(-m_owner->GetCamera()->GetForward() * 35.0f);
        }
        m_owner->Rotate();

        rigidbody->ApplyFriction();
    }
}

/**
 * \brief 終了処理.
 * 
 */
void PlayerMoveState::OnExit()
{
}
