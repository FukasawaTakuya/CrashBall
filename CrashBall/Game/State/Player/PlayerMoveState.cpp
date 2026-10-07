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
#include "Game/Engine/Time.h"

using namespace DirectX;

/**
 * \brief コンストラクタ.
 * 
 */
PlayerMoveState::PlayerMoveState(const PlayerStateContext& stateContext)
    : PlayerStateBase(stateContext)
{
    m_targetCameraController
        = stateContext.playerController->GetCamera()->GetGameObject()->GetComponent<TargetCameraController>();
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
    using namespace SimpleMath;
    // イージングの初期化
    m_ambient.Initialize([&](const Color& start, const Color& end, float t) { return Color::Lerp(start, end, t); });
    // イージングの設定
    m_ambient.Set(
        Ease::Linear,
        m_stateContext.modelRenderer->GetAmbientColor(),
        m_stateContext.playerStatusController->GetDefaultAmbient(),
        0.5f);

    // 攻撃実行フラグを下げる
    m_stateContext.playerStatusController->SetGoAttack(false);

    m_targetCameraController->SetZoomRate(1.0f);
}

/**
 * \brief 更新処理
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void PlayerMoveState::Update(const GameContext& gameContext)
{
    // 物理演算コンポーネント
    Rigidbody* rigidbody = m_stateContext.rigidbody;
    // プレイヤー操作コンポーネント
    PlayerController* playerController = m_stateContext.playerController;
    // プレイヤーステータス操作コンポーネント
    PlayerStatusController* playerStatusController = m_stateContext.playerStatusController;
    // 
    ModelRenderer* modelRenderer = m_stateContext.modelRenderer;

    SimpleMath::Vector3 moveValue = SimpleMath::Vector3(
        Input::GetGamePad().thumbSticks.leftX,
        0.0f,
        Input::GetGamePad().thumbSticks.leftY
    );

    // 地上にいる場合
    if (m_stateContext.ballController->GetIsGround())
    {
        rigidbody->Accel(playerController->GetCamera()->GetHorizontalRight() * moveValue.x * playerController->GetAcceleration());
        rigidbody->Accel(playerController->GetCamera()->GetHorizontalForward() * moveValue.z * playerController->GetAcceleration());
        // 入力に応じて加速
        if (Input::GetKeyDown(Keyboard::D)) {
            rigidbody->Accel( playerController->GetCamera()->GetHorizontalRight()   * playerController->GetAcceleration());
        }
        if (Input::GetKeyDown(Keyboard::A)) {
            rigidbody->Accel(-playerController->GetCamera()->GetHorizontalRight()   * playerController->GetAcceleration());
        }
        if (Input::GetKeyDown(Keyboard::W)) {
            rigidbody->Accel( playerController->GetCamera()->GetHorizontalForward() * playerController->GetAcceleration());
        }
        if (Input::GetKeyDown(Keyboard::S)) {
            rigidbody->Accel(-playerController->GetCamera()->GetHorizontalForward() * playerController->GetAcceleration());
        }
    }

    // スペースキーが押されたとき攻撃が可能なら攻撃ステートに遷移
    if ((Input::GetKeyTrigger(DirectX::Keyboard::Space) || 
        Input::GetGamePadTracker()->a == GamePad::ButtonStateTracker::ButtonState::PRESSED)&&
        playerStatusController->GetCanAttack() && !playerStatusController->GetGoAttack())
    {
        // 面消費
        playerController->GetPaintConsumer()->ConsumePaint(playerStatusController->GetAttacckCost());

        // イージングの設定
        m_ambient.Set(
            Ease::Linear,
            modelRenderer->GetAmbientColor(),
            playerStatusController->GetAttackAmbient(),
            0.5f);

        playerStatusController->SetGoAttack(true);
    }

    m_ambient.DoEase(Time::GetElapsedTime());
    modelRenderer->SetAmbientColor(m_ambient.GetValue());

    if (playerStatusController->GetGoAttack())
    {
        if (!m_ambient.IsEase())
        {
            // ステートの遷移
            m_pStateMachine->ChangeState<PlayerAttackState>();
            // 音の再生
            gameContext.soundManager->RegisterPlaySeCommand("Attack");
            // 攻撃フラグを設定
            playerStatusController->SetIsAttack(true);
        }
        else
        {
            rigidbody->SetVelocity(SimpleMath::Vector3::Zero);
        }
    }

    // 速度制限
	if (rigidbody->GetVelocity().Length() > playerController->GetMaxSpeed())
		rigidbody->SetVelocity(XMVector3Normalize(rigidbody->GetVelocity()) * playerController->GetMaxSpeed());
}

/**
 * \brief 終了処理.
 * 
 */
void PlayerMoveState::OnExit()
{
}
