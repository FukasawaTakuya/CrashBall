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
    // 物理演算コンポーネント
    Rigidbody* rigidbody = m_stateContext.rigitbody;
    // プレイヤー操作コンポーネント
    PlayerController* playerController = m_stateContext.playerController;
    // プレイヤーステータス操作コンポーネント
    PlayerStatusController* playerStatusController = m_stateContext.playerStatusController;

    // 地上にいる場合
    if (m_stateContext.ballController->GetIsGround())
    {
        // 入力に応じて加速
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

    // スペースキーが押されたとき攻撃が可能なら攻撃ステートに遷移
    if (Input::GetKeyTrigger(DirectX::Keyboard::Space) &&
        playerStatusController->GetCanAttack())
    {
        // ステートの遷移
		m_pStateMachine->ChangeState<PlayerAttackState>();
        // 面消費
        playerController->GetPaintConsumer()->ConsumePaint(playerStatusController->ATTACK_COST);
        // 攻撃フラグを設定
        playerStatusController->SetIsAttack(true);
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
