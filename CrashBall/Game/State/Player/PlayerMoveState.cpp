/*****************************************************************//**
 * \file   PlayerMoveState.cpp
 * \brief  プレイヤー移動ステートに関するソースファイル
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

// ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "PlayerMoveState.h"
#include "Game/GameObject/Player/Player.h"
#include "Game/Common/InputSystem.h"
#include "Game/Common/Camera.h"
#include "PlayerJumpState.h"
#include "PlayerAttackState.h"

// メンバ関数の定義 ===================================================

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
    // キー情報の取得
    auto key = Keyboard::Get().GetState();
    // 物理演算コンポーネントの取得
    RigidBody* rigidbody = m_owner->GetComponent<RigidBody>();
	// トランスフォームコンポーネントの取得
	Transform* transform = m_owner->GetComponent<Transform>();

    // 加速度のリセット
    rigidbody->ResetAccel();

    // 地上にいる場合
    if (m_owner->GetIsGround())
    {
        if (key.D) {
            rigidbody->Accel( m_owner->GetCamera()->GetRight()   * ACCELERATION);
        }
        if (key.A) {
            rigidbody->Accel(-m_owner->GetCamera()->GetRight()   * ACCELERATION);
        }
        if (key.W) {
            rigidbody->Accel( m_owner->GetCamera()->GetForward() * ACCELERATION);
        }
        if (key.S) {
            rigidbody->Accel(-m_owner->GetCamera()->GetForward() * ACCELERATION);
        }
        m_owner->Ball::Rotate();
    }

    if (InputSystem::Instance().IsKeyTrigger(DirectX::Keyboard::Space))
    {
		m_pStateMachine->ChangeState<PlayerAttackState>();
    }

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
