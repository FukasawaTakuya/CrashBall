/*****************************************************************//**
 * \file   EnemyWanderState.cpp
 * \brief  敵の徘徊ステートに関するソースファイル
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#include "pch.h"
#include "EnemyWanderState.h"
#include "Game/GameObject/Enemy/Enemy.h"
#include "Game/GameObject/Stage.h"
#include "Game/Common/Random.h"
#include "Game/ServiceLocator/TimeService.h"

using namespace DirectX;

/**
 * @brief コンストラクタ
 * 
 */
EnemyWanderState::EnemyWanderState()
{
}

/**
 * @brief デストラクタ
 * 
 */
EnemyWanderState::~EnemyWanderState()
{
}

/**
 * \brief 初期化処理
 * 
 */
void EnemyWanderState::Initialize()
{
}

/**
 * @brief 開始処理
 * 
 */
void EnemyWanderState::OnEnter()
{
	m_timer = DIRECTION_CHANGE_INTERVAL;
}

/**
 * @brief 更新処理
 * 
 */
void EnemyWanderState::Update()
{
	Transform* transform = m_owner->GetComponent<Transform>();
	RigidBody* rigidbody = m_owner->GetComponent<RigidBody>();

	float elapsedTime 
		= TimeService::Instance().GetTime()->GetElapsedTime();
	m_timer += elapsedTime;

	// 加速度のリセット
	rigidbody->ResetAccel();

	// 水平移動のみを正規化して取得
	SimpleMath::Vector3 direction = rigidbody->GetVelocity();
	direction.y = 0.0f;
	direction.Normalize();

	// 加速度方向を取得
	SimpleMath::Vector3 accelDirection = m_owner->GetAccelDirection();

	if (m_timer >= DIRECTION_CHANGE_INTERVAL)
	{
		// 円の中心
		SimpleMath::Vector3 circleCenter =
			transform->GetPosition() + direction * DIRECTION_CIRCLE_DISTANCE;

		// 円の角度を更新
		float circleRadian = Random::Instance().Range(0.0f, XM_2PI);

		// 円周上の点
		SimpleMath::Vector3 circlePoint = circleCenter +
			SimpleMath::Vector3(std::cos(circleRadian), 0.0f, std::sin(circleRadian)) * DIRECTION_CIRCLE_RADIUS;

		// 進行方向を更新
		accelDirection = XMVector3Normalize(circlePoint - transform->GetPosition());

		// 進行方向を水平移動のみにする
		accelDirection.y = 0.0f;
		accelDirection.Normalize();

		// タイマーをリセット
		m_timer = 0.0f;
	}
	
	// 加速方向を設定
	m_owner->SetAccelDirection(accelDirection);
}

/**
 * @brief 終了処理
 * 
 */
void EnemyWanderState::OnExit()
{
}