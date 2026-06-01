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
    // プレイヤー操作コンポーネントの取得
    PlayerController* playerController = m_stateContext.playerController;

    // 地上にいる場合
    if (m_stateContext.ballController->GetIsGround())
    {
        if (Input::GetKeyDown(Keyboard::D)) {
            rigidbody->Accel( playerController->GetCamera()->GetRight()   * ACCELERATION);
        }
        if (Input::GetKeyDown(Keyboard::A)) {
            rigidbody->Accel(-playerController->GetCamera()->GetRight()   * ACCELERATION);
        }
        if (Input::GetKeyDown(Keyboard::W)) {
            rigidbody->Accel( playerController->GetCamera()->GetForward() * ACCELERATION);
        }
        if (Input::GetKeyDown(Keyboard::S)) {
            rigidbody->Accel(-playerController->GetCamera()->GetForward() * ACCELERATION);
        }
    }

    // スペースキーが押されたら攻撃ステートに遷移
    if (Input::GetKeyTrigger(DirectX::Keyboard::Space))
    {
		m_pStateMachine->ChangeState<PlayerAttackState>();
        // TODO:面消費通知 
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
