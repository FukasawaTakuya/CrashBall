#include "pch.h"
#include "EnemyWanderState.h"
#include "Game/Common/Random.h"
#include "Game/Common/TimeManager.h"
#include "Game/GameObject/Enemy/Enemy.h"

using namespace DirectX;

/**
 * @brief コンストラクタ
 * 
 */
EnemyWanderState::EnemyWanderState()
	: m_directionCircleRadian{}
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
 * @brief 開始処理
 * 
 */
void EnemyWanderState::OnEnter()
{
}

/**
 * @brief 更新処理
 * 
 */
void EnemyWanderState::Update()
{
	if (m_timer >= 1.0f)
	{
		Transform* transform = m_owner->GetComponent<Transform>();
		RigidBody* rigidBody = m_owner->GetComponent<RigidBody>();

		// 円の中心
		SimpleMath::Vector3 circleCenter =
			transform->GetPosition() + m_owner->GetDirection() * DIRECTION_CIRCLE_DISTANCE;

		// 円の角度を更新
		float circleRadian = Random::Instance().Range(0.0f, XM_2PI);

		// 円周上の点
		SimpleMath::Vector3 circlePoint = circleCenter +
			SimpleMath::Vector3(std::cos(circleRadian), 0.0f, std::sin(circleRadian)) * DIRECTION_CIRCLE_RADIUS;

		// 進行方向を更新
		m_targetDirection = XMVector3Normalize(circlePoint - transform->GetPosition());

		m_targetDirection.y = 0.0f;
		m_targetDirection.Normalize();

		m_timer = 0.0f;
	}
	
	m_timer += TimeManager::Instance().GetElapsedTime();

	// 進行方向を徐々に変える
	m_owner->SetDirection(SimpleMath::Vector3::Lerp(
		m_owner->GetDirection(), m_targetDirection, TimeManager::Instance().GetElapsedTime() * 2.0f));
}

/**
 * @brief 終了処理
 * 
 */
void EnemyWanderState::OnExit()
{
}
