/*****************************************************************//**
 * \file   PlayerMoveState.cpp
 * \brief  プレイヤー移動ステート 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#include "pch.h"
#include "PlayerMoveState.h"
#include "PlayerAttackState.h"

#include "Game/Engine/Input.h"

using namespace DirectX;

/**
 * \brief コンストラクタ.
 * 
 */
PlayerMoveState::PlayerMoveState(const PlayerStateContext& stateContext)
    : PlayerStateBase(stateContext)
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
    RigidBody* rigidbody = m_stateContext.rigitbody;

    // 地上にいる場合
    if (m_owner->GetGameObject()->GetComponent<BallController>()->GetIsGround())
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
    }

    // スペースキーが押されたら攻撃ステートに遷移
    if (Input::GetKeyTrigger(DirectX::Keyboard::Space))
    {
		m_pStateMachine->ChangeState<PlayerAttackState>();
        // TODO:面消費通知 PlayerController移行
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
