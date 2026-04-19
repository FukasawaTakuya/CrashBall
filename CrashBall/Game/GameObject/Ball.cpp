#include "pch.h"
#include "Ball.h"

#include "Game/CommonResources/CommonResources.h"

using namespace DirectX;

Ball::Ball(SimpleMath::Vector3 pos, float radius)
{
}

void Ball::Initialize()
{
}

void Ball::Update(float elapsedTime)
{
	Move();
}

void Ball::Draw(SimpleMath::Matrix proj, SimpleMath::Matrix view)
{
	auto context = CommonResources::Instance().GetContext();
	auto state = CommonResources::Instance().GetState();

	m_quaternion *= m_quaternion;

	SimpleMath::Matrix scale = SimpleMath::Matrix::CreateScale(0.025f);
	SimpleMath::Matrix rotate = SimpleMath::Matrix::CreateFromQuaternion(m_quaternion);
	SimpleMath::Matrix trans = SimpleMath::Matrix::CreateTranslation(m_transform->GetPosition());

	SimpleMath::Matrix world
		= scale * rotate * trans;

	m_pModel->Draw(context, *state, world, view, proj);
}

void Ball::Accelarate(DirectX::SimpleMath::Vector3 accel)
{
	m_rbody->Accel(accel);
}

void Ball::Move()
{
	m_rbody->ApplyAccel();

	// 速度を加算
	m_transform->Translate(m_rbody->GetVelocity()); /** elapsedTime*/;
}

void Ball::Rotate()
{
	SimpleMath::Vector3 velocity = m_rbody->GetVelocity();

	// 進行方向のベクトル
	SimpleMath::Vector3 dire = velocity;
	dire.Normalize();

	SimpleMath::Vector3 v = SimpleMath::Vector3::Up;

	// 進行方向に垂直なベクトルを求める
	SimpleMath::Vector3 horizontalDirection = v.Cross(dire);

	// ゼロベクトルならリターン
	if (horizontalDirection == SimpleMath::Vector3::Zero) return;

	// 回転量を求める
	float forwardAngle = velocity.Length() /** elapsedTime / m_collider->GetRadius()*/;

	// クオータニオンを求める
	m_quaternion = SimpleMath::Quaternion::CreateFromAxisAngle(horizontalDirection, forwardAngle);
}

void Ball::ApplyFriction()
{
	if (m_rbody->GetVelocity().LengthSquared())
		m_rbody->ApplyFriction();
}
