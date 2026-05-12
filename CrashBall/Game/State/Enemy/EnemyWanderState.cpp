/*****************************************************************//**
 * \file   EnemyWanderState.cpp
 * \brief  敵の徘徊ステートに関するソースファイル
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "EnemyWanderState.h"
#include "Game/GameObject/Enemy/Enemy.h"
#include "Game/Common/Random.h"
#include "Game/Common/TimeManager.h"
#include "Game/GameObject/Floor.h"

// 名前空間の使用 ============================================================
using namespace DirectX;

// メンバ関数の定義 ===============================================================

/**
 * @brief コンストラクタ
 * 
 */
EnemyWanderState::EnemyWanderState()
	: m_directionCircleRadian{}
	, m_timer{ 1.0f }
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
}

/**
 * @brief 更新処理
 * 
 */
void EnemyWanderState::Update()
{
	// コンポーネントの取得
	Transform* transform = m_owner->GetComponent<Transform>();
	RigidBody* rigidbody = m_owner->GetComponent<RigidBody>();
	// 前フレームの経過時間の取得
	float elapsedTime = TimeManager::Instance().GetElapsedTime();

	// 加速度のリセット
	rigidbody->ResetAccel();

	// タイマーを更新
	m_timer += elapsedTime;

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