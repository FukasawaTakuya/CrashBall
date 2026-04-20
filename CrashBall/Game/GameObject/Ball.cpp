#include "pch.h"
#include "Ball.h"

#include "Game/Common/CommonResources.h"
#include "Game/Common/TimeManager.h"

using namespace DirectX;

Ball::Ball(SimpleMath::Vector3 pos, float radius)
	: m_isGround{false}
{
	AddComponent<Transform>();
	AddComponent<RigitBody>(GRAVITY, FRICTION);
	AddComponent<Sphere>(0.5f);

	m_transform = GetComponent<Transform>();
	m_rigitbody = GetComponent<RigitBody>();
	m_collider	= GetComponent<Sphere>();

	m_transform->SetPosition(pos);
	m_rigitbody->SetVelocity(SimpleMath::Vector3::Zero);
}

void Ball::Initialize()
{
}

void Ball::Update(float elapsedTime)
{
}

void Ball::Draw(SimpleMath::Matrix proj, SimpleMath::Matrix view)
{
	auto context = CommonResources::Instance().GetContext();
	auto state = CommonResources::Instance().GetState();

	m_transform->RotateQuaternion(m_rotateValue);

	SimpleMath::Matrix scale 
		= SimpleMath::Matrix::CreateScale(0.025f);
	SimpleMath::Matrix rotate 
		= SimpleMath::Matrix::CreateFromQuaternion(m_transform->GetQuaternion());
	SimpleMath::Matrix trans 
		= SimpleMath::Matrix::CreateTranslation(m_transform->GetPosition());

	SimpleMath::Matrix world
		= scale * rotate * trans;

	m_pModel->Draw(context, *state, world, view, proj);
}

void Ball::Accelarate(DirectX::SimpleMath::Vector3 accel)
{
	m_rigitbody->Accel(accel);
}

void Ball::Move()
{
	// 重力の適用
	m_rigitbody->ApplyGravity();

	// 加速度の適用
	m_rigitbody->ApplyAccel();

	// 速度を加算
	m_transform->Translate(m_rigitbody->GetVelocity() * TimeManager::Instance().GetElapsedTime());

	// コライダーの座標の更新
	m_collider->SetPos(m_transform->GetPosition());
}

void Ball::Rotate()
{
	SimpleMath::Vector3 velocity = m_rigitbody->GetVelocity();

	// 進行方向のベクトル
	SimpleMath::Vector3 dire = velocity;
	dire.Normalize();

	SimpleMath::Vector3 v = SimpleMath::Vector3::Up;

	// 進行方向に垂直なベクトルを求める
	SimpleMath::Vector3 horizontalDirection = v.Cross(dire);

	// ゼロベクトルならリターン
	if (horizontalDirection == SimpleMath::Vector3::Zero) return;

	// 回転量を求める
	float forwardAngle = velocity.Length() * TimeManager::Instance().GetElapsedTime() / m_collider->GetRadius();

	// クオータニオンを求める
	m_rotateValue = SimpleMath::Quaternion::CreateFromAxisAngle(horizontalDirection, forwardAngle);

}
