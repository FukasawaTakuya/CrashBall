#include "pch.h"
#include "BallController.h"
#include "Game/Engine/Time.h"

BallController::BallController(IGameObject* owner)
	: Component(owner)
{
	m_transform			= GetGameObject()->GetComponent<Transform>();
	m_rigidbody			= GetGameObject()->GetComponent<RigidBody>();
	m_sphereCollider	= GetGameObject()->GetComponent<Sphere>();
}

BallController::~BallController()
{
}

void BallController::Initialize()
{
}

void BallController::Update(GameContext gameContext)
{
	// 移動
	Move();

	// 地上なら回転を加算する
	if (m_isGround)
	{
		AddRotate();
	}

	// 回転
	Rotate();
}

void BallController::Move()
{
	// 重力の適用
	m_rigidbody->ApplyGravity();

	// 加速度の適用
	m_rigidbody->ApplyAccel();

	// 地上なら
	if (m_isGround)
		// 摩擦の適用
		m_rigidbody->ApplyFriction();

	// 速度を加算
	m_transform->Translate(m_rigidbody->GetVelocity() * Time::GetElapsedTime());

	// 加速度のリセット
	m_rigidbody->ResetAccel();
}

void BallController::AddRotate()
{
	// 速度の取得
	const SimpleMath::Vector3& velocity = m_rigidbody->GetVelocity();

	// 進行方向
	SimpleMath::Vector3 dire = XMVector3Normalize(velocity);

	SimpleMath::Vector3 v = SimpleMath::Vector3::Up;

	// 進行方向に垂直なベクトルを求める
	SimpleMath::Vector3 horizontalDirection
		= XMVector3Cross(SimpleMath::Vector3::Up, velocity);

	// ゼロベクトルならリターン
	if (horizontalDirection == SimpleMath::Vector3::Zero) return;

	// 回転量を求める
	float forwardAngle
		= velocity.Length() * Time::GetElapsedTime() / m_sphereCollider->GetRadius();

	// 角速度を求める
	SimpleMath::Quaternion quaternion
		= SimpleMath::Quaternion::CreateFromAxisAngle(horizontalDirection, forwardAngle);
	m_angularVelocity = quaternion;
}

void BallController::Rotate()
{
	// 回転
	m_transform->Rotate(m_angularVelocity);
}
