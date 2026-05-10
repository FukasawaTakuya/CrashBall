#include "pch.h"
#include "EnemyWanderState.h"
#include "Game/Common/Random.h"
#include "Game/Common/TimeManager.h"
#include "Game/GameObject/Enemy/Enemy.h"
#include "Game/Component/Collider/Segment.h"
#include "Game/GameObject/Floor.h"
#include "Game/CollisionManager/Collision.h"
#include <Game/Renderer/PrimitveRendererManager.h>

using namespace DirectX;

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

	// 地上にいるときのみ徘徊する
	if (!m_owner->GetIsGround()) return;

	if (m_currentDirection == SimpleMath::Vector3::Zero)
	{
		float randomRadian = Random::Instance().Range(0.0f, XM_2PI);
		m_currentDirection = { std::cos(randomRadian), 0.0f, std::sin(randomRadian) };
	};

	// 水平移動のみを正規化して取得
	SimpleMath::Vector3 direction = { rigidbody->GetVelocity().x, 0.0f, rigidbody->GetVelocity().z };
	direction.Normalize();

	if (m_timer >= 1.0f)
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
		m_targetDirection = XMVector3Normalize(circlePoint - transform->GetPosition());

		// 進行方向を水平移動のみにする
		m_targetDirection.y = 0.0f;
		m_targetDirection.Normalize();

		// タイマーをリセット
		m_timer = 0.0f;
	}
	
	m_timer += elapsedTime;

	m_currentDirection = 
		SimpleMath::Vector3::Lerp(m_currentDirection, m_targetDirection, elapsedTime * 5.0f);

	// 壁回避処理
	AvoidWall(rigidbody, transform);

	// 進行方向を徐々に変える
	rigidbody->Accel(m_targetDirection * WANDER_ACCELERATION);

	//OutputDebugString(L"current x:%f y:%f z:%f\n ", m_currentDirection.x, m_currentDirection.y, m_currentDirection.z);
	//OutputDebugString(L"target x:%f y:%f z:%f\n ", m_targetDirection.x, m_targetDirection.y, m_targetDirection.z);

	std::vector<DirectX::VertexPositionNormalColor> pos
	{
		VertexPositionNormalColor(transform->GetPosition(), SimpleMath::Vector3::Up, Colors::Black),
		VertexPositionNormalColor(transform->GetPosition() + m_currentDirection * 3.0f, SimpleMath::Vector3::Up, Colors::Black),
	};

	std::vector<DirectX::VertexPositionNormalColor> pos2
	{
		VertexPositionNormalColor(transform->GetPosition(), SimpleMath::Vector3::Up, Colors::Red),
		VertexPositionNormalColor(transform->GetPosition() + m_targetDirection * 3.0f, SimpleMath::Vector3::Up, Colors::Red),
	};

	PrimitiveRendererManager::Instance().RegisterDrawCommand({
		D3D10_PRIMITIVE_TOPOLOGY_LINELIST
		, pos
		});

	
}

/**
 * @brief 終了処理
 * 
 */
void EnemyWanderState::OnExit()
{
}

/**
 * @brief 壁回避処理
 * 
 */
void EnemyWanderState::AvoidWall(RigidBody* rigidbody, Transform* transform)
{
	MeshFloor* floor = m_owner->GetFloor();
	for (auto& face : floor->GetMesh()->GetFace())
	{
			if (face->GetPlane()->GetNormal().y < 0.3f && face->GetPlane()->GetNormal().y > 0.0f)
			{
				if ((face->GetPlane()->CalcLength(transform->GetPosition()) <= 6.0f))
				{

					SimpleMath::Vector3 faceNormal = face->GetPlane()->GetNormal();
					faceNormal.y = 0.0f;
					faceNormal.Normalize();

					SimpleMath::Vector3 vn = faceNormal.Dot(m_targetDirection) * faceNormal;
					SimpleMath::Vector3 vt = m_targetDirection - vn;

					m_targetDirection = vt + faceNormal;
					m_targetDirection.Normalize();
					m_timer = 0.0f;

					m_currentDirection = m_targetDirection;
				
					return;
				}
			}
	}
}
