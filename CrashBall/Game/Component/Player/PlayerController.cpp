/*****************************************************************//**
 * \file   PlayerController.cpp
 * \brief  プレイヤー操作コンポーネント
 *
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#include "pch.h"
#include "PlayerController.h"

#include "Game/State/Player/PlayerMoveState.h"
#include "Game/State/Player/PlayerAttackState.h"

/**
 * \brief コンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 */
PlayerController::PlayerController(IGameObject* gameObject)
	: Component(gameObject)
	, m_stateMachine(std::make_unique<StateMachine<PlayerController>>(this))
{
	// プレイヤーステート用のコンテキスト
	PlayerStateContext stateContext
	{
		GetGameObject()->GetComponent<Rigidbody>(),
		GetGameObject()->GetComponent<Transform>(),
		GetGameObject()->GetComponent<BallController>(),
		GetGameObject()->GetComponent<PlayerStatusController>(),
		this
	};

	// ステートの生成
	m_stateMachine->CreateState<PlayerMoveState>(stateContext);
	m_stateMachine->CreateState<PlayerAttackState>(stateContext);

	// 初期のステートのセット
	m_stateMachine->ChangeState<PlayerMoveState>();
}

/**
 * \brief コピーコンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 * \param playerController プレイヤー操作コンポーネント
 */
PlayerController::PlayerController(
	IGameObject* gameObject,
	const PlayerController& playerController)
	: Component(gameObject)
	, m_stateMachine	(std::make_unique<StateMachine<PlayerController>>(this))
	, m_attackSpeed		(playerController.m_attackSpeed)
	, m_attackDuration	(playerController.m_attackDuration)
	, m_acceleration	(playerController.m_acceleration)
	, m_maxSpeed		(playerController.m_maxSpeed)
{
	// プレイヤーステート用のコンテキスト
	PlayerStateContext stateContext
	{
		GetGameObject()->GetComponent<Rigidbody>(),
		GetGameObject()->GetComponent<Transform>(),
		GetGameObject()->GetComponent<BallController>(),
		GetGameObject()->GetComponent<PlayerStatusController>(),
		this
	};

	// ステートの生成
	m_stateMachine->CreateState<PlayerMoveState>(stateContext);
	m_stateMachine->CreateState<PlayerAttackState>(stateContext);

	// 初期のステートのセット
	m_stateMachine->ChangeState<PlayerMoveState>();
}

/**
 * \brief デストラクタ
 * 
 */
PlayerController::~PlayerController()
{
}

/**
 * \brief 初期化
 * 
 */
void PlayerController::Initialize()
{
}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void PlayerController::Update(const GameContext& gameContext)
{
	// ステートマシンの更新
	if (m_stateMachine != nullptr)
		m_stateMachine->Update();
}
