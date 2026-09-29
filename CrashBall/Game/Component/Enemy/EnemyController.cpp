/*****************************************************************//**
 * \file   EnemyController.cpp
 * \brief  敵操作コンポーネント
 *
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/


#include "pch.h"
#include "EnemyController.h"
#include "Game/State/Enemy/EnemyWanderState.h"
#include "Game/Component/Ball/BallController.h"

#include "Game/ScriptableObject/Scriptable.h"

using namespace DirectX;

RegisterComponent(EnemyController)


/**
 * \brief コンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 */
EnemyController::EnemyController(IGameObject* gameObject)
	: Component(gameObject)
	, m_stateMachine{ std::make_unique<StateMachine<EnemyController>>(this) }
{
}

/**
 * \brief デストラクタ
 * 
 */
EnemyController::~EnemyController()
{
}

/**
 * \brief アタッチ時の処理
 * 
 */
void EnemyController::Awake()
{
	// 敵ステート用のコンテキスト
	EnemyStateContext stateContext{
			GetGameObject()->GetComponent<Transform>(),
			GetGameObject()->GetComponent<Rigidbody>(),
			this
	};

	// ステートの生成
	m_stateMachine->CreateState<EnemyWanderState>(stateContext);

	// 初期ステートの設定
	m_stateMachine->ChangeState<EnemyWanderState>();

	// コンポーネントのキャッシュ
	m_transform = GetGameObject()->GetComponent<Transform>();
	m_rigidbody = GetGameObject()->GetComponent<Rigidbody>();
	m_modelRenderer = GetGameObject()->GetComponent<ModelRenderer>();
	m_ballController = GetGameObject()->GetComponent<BallController>();

	GetGameObject()->GetComponent<ModelRenderer>()->SetDiffuseColor(
		Scriptable::GetScriptableObject<GameColor>()->m_enemyColor
	);

}

/**
 * \brief 初期化
 * 
 */
void EnemyController::Start(const GameContext& gameContext)
{
	// HPの初期化
	m_hp = m_maxHp;
	// 移動速度を0に設定
	m_rigidbody->SetVelocity(SimpleMath::Vector3::Zero);
}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void EnemyController::Update(const GameContext& gameContext)
{
	// ステートの更新
	if (m_stateMachine != nullptr)
		m_stateMachine->Update(gameContext);

	// 地上にいるとき
	if (m_ballController->GetIsGround())
	{
		// 壁回避
		AvoidWall();
		// 加速
		m_rigidbody->Accel(m_accelDirection * m_acceleration);
	}
}

/**
 * \brief ダメージ処理
 * 
 * \param damage ダメージ
 */
void EnemyController::Damage(float damage)
{
	m_hp = std::clamp(m_hp - damage, 0.0f, m_maxHp);
}

/**
 * \brief 壁回避
 * 
 */
void EnemyController::AvoidWall()
{
	// 
	if (m_transform->GetWorldPosition().Length() - m_pDoom->GetRadius() <= m_avoidDoomDistance)
	{
		// ドームの中心に向かうベクトル
		SimpleMath::Vector3 doomDire 
			= -(m_transform->GetWorldPosition() - m_pDoom->GetTransform()->GetWorldPosition());
		// 水平方向に直す
		doomDire.y = 0.0f;
		doomDire.Normalize();

		// ドームの外に向かって加速しているなら速度を補正
		if (m_accelDirection.Dot(-doomDire) > 0.0f)
		{
			// 加速度のドームの外方向のベクトル成分
			SimpleMath::Vector3 vn = -doomDire.Dot(m_accelDirection) * -doomDire;
			// 接線ベクトルを求める
			SimpleMath::Vector3 vt = m_accelDirection - vn;

			// 加速方向に接線ベクトルを設定
			m_accelDirection = vt;
			m_accelDirection.Normalize();
		}

		// 進行方向
		SimpleMath::Vector3 direction = XMVector3Normalize(m_rigidbody->GetVelocity());
		// ドームの外に向かって移動しているなら強い力で速度を補正
		if (direction.Dot(-doomDire) > 0.0f)
		{
			m_rigidbody->Accel(doomDire * m_avoidDoomStrongForce);
		}
		// 弱い力で速度を補正
		else
		{
			m_rigidbody->Accel(doomDire * m_avoidDoomWeakForce);
		}
	}
}
