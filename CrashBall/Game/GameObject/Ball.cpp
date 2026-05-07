/*****************************************************************//**
 * \file   Ball.cpp
 * \brief  ボールクラスに関するソースファイル
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#include "pch.h"
#include "Ball.h"
#include "Game/Common/TimeManager.h"

using namespace DirectX;

Ball::Ball(float radius)
{
	// コンポーネントの追加
	m_transform = AddComponent<Transform>();
	m_rigitbody = AddComponent<RigitBody>(GRAVITY, FRICTION);
	m_collider	= AddComponent<Sphere>(m_transform, radius);
	m_renderer	= AddComponent<ModelRenderer>();

	m_collider->SetLayerMask(LayerMask::Ball);
}

void Ball::Initialize(SimpleMath::Vector3 position)
{
	m_transform->SetPosition(position);
	m_rigitbody->SetVelocity(SimpleMath::Vector3::Zero);
}

void Ball::Draw()
{
	m_transform->Rotate(m_rotateValue);

	// 拡大行列
	SimpleMath::Matrix scale 
		= SimpleMath::Matrix::CreateScale(0.025f);
	// 回転行列
	SimpleMath::Matrix rotate 
		= m_transform->GetRotate();
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
}

void Ball::Rotate()
{
	const SimpleMath::Vector3& velocity = m_rigitbody->GetVelocity();

	// 進行方向のベクトル
	SimpleMath::Vector3 dire = XMVector3Normalize(velocity);

	SimpleMath::Vector3 v = SimpleMath::Vector3::Up;

	// 進行方向に垂直なベクトルを求める
	SimpleMath::Vector3 horizontalDirection 
		= XMVector3Cross(SimpleMath::Vector3::Up, velocity);

	// ゼロベクトルならリターン
	if (horizontalDirection == SimpleMath::Vector3::Zero) return;

	// 回転量を求める
	float forwardAngle 
		= velocity.Length() * TimeManager::Instance().GetElapsedTime() / m_collider->GetRadius();

	// 回転値を求める
	SimpleMath::Quaternion quaternion
		= SimpleMath::Quaternion::CreateFromAxisAngle(horizontalDirection, forwardAngle);

	// 回転量をマトリクスに変換
	m_rotateValue = SimpleMath::Matrix::CreateFromQuaternion(quaternion);
}
