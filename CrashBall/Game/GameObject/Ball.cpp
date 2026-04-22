#include "pch.h"
#include "Ball.h"
#include "Game/Common/TimeManager.h"

using namespace DirectX;

Ball::Ball(SimpleMath::Vector3 pos, float radius)
	: m_isGround{false}
{
	// コンポーネントの追加
	m_transform = AddComponent<Transform>();
	m_rigitbody = AddComponent<RigitBody>(GRAVITY, FRICTION);
	m_collider	= AddComponent<Sphere>(0.5f);
	m_renderer	= AddComponent<ModelRenderer>();

	m_transform->SetPosition(pos);
	m_rigitbody->SetVelocity(SimpleMath::Vector3::Zero);
}

void Ball::Initialize()
{
}

void Ball::Update(float elapsedTime)
{
}

void Ball::Draw()
{
	// クオータニオンを回転させる
	m_transform->RotateQuaternion(m_rotateValue);

	// 拡大行列
	SimpleMath::Matrix scale 
		= SimpleMath::Matrix::CreateScale(0.025f);
	// 回転行列
	SimpleMath::Matrix rotate 
		= SimpleMath::Matrix::CreateFromQuaternion(m_transform->GetQuaternion());
	// 移動行列
	SimpleMath::Matrix trans 
		= SimpleMath::Matrix::CreateTranslation(m_transform->GetPosition());

	// ワールド行列
	SimpleMath::Matrix world = scale * rotate * trans;

	// 描画
	m_renderer->Draw(world);
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

	// 回転値を求める
	m_rotateValue = SimpleMath::Quaternion::CreateFromAxisAngle(horizontalDirection, forwardAngle);

}
