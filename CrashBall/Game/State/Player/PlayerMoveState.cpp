/*****************************************************************//**
 * \file   PlayerMoveState.cpp
 * \brief  プレイヤー移動ステート 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#include "pch.h"
#include "PlayerMoveState.h"
#include "PlayerJumpState.h"
#include "PlayerAttackState.h"
#include "Game/GameObject/Player/Player.h"
#include "Game/Common/Camera.h"
#include "Game/Engine/Input.h"

using namespace DirectX;

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
 * \brief 初期化処理.
 * 
 */
void PlayerMoveState::Initialize()
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
    // 物理演算コンポーネントの取得
    RigidBody* rigidbody = m_owner->GetComponent<RigidBody>();
	// トランスフォームコンポーネントの取得
	Transform* transform = m_owner->GetComponent<Transform>();

    // 加速度のリセット
    rigidbody->ResetAccel();

    // 地上にいる場合
    if (m_owner->GetIsGround())
    {
        if (Input::GetKeyDown(Keyboard::D)) {
            rigidbody->Accel( m_owner->GetCamera()->GetRight()   * ACCELERATION);
        }
        if (Input::GetKeyDown(Keyboard::A)) {
            rigidbody->Accel(-m_owner->GetCamera()->GetRight()   * ACCELERATION);
        }
        if (Input::GetKeyDown(Keyboard::W)) {
            rigidbody->Accel( m_owner->GetCamera()->GetForward() * ACCELERATION);
        }
        if (Input::GetKeyDown(Keyboard::S)) {
            rigidbody->Accel(-m_owner->GetCamera()->GetForward() * ACCELERATION);
        }
        m_owner->Ball::Rotate();
    }

    // スペースキーが押されたら攻撃ステートに遷移
    if (Input::GetKeyTrigger(DirectX::Keyboard::Space))
    {
		m_pStateMachine->ChangeState<PlayerAttackState>();
    }

    // 速度制限
	if (rigidbody->GetVelocity().Length() > MAX_SPEED)
		rigidbody->SetVelocity(XMVector3Normalize(rigidbody->GetVelocity()) * MAX_SPEED);
}

/**
 * \brief 終了処理.
 * 
 */
void PlayerMoveState::OnExit()
{
}
