/*****************************************************************//**
 * \file   Ball.cpp
 * \brief  ボールクラスに関するソースファイル
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Ball.h"
#include "Game/Common/TimeManager.h"

using namespace DirectX;

// メンバ関数の定義 ===========================================================

Ball::Ball(float radius, ObjectTag tag)
	: GameObject(tag)
{
	// コンポーネントの追加
	m_transform = AddComponent<Transform>();
	m_rigidBody = AddComponent<RigidBody>(GRAVITY, FRICTION);
	m_collider	= AddComponent<Sphere>(m_transform, radius);
	m_renderer	= AddComponent<ModelRenderer>();

	m_collider->SetLayerMask(LayerMask::Ball);

	// 衝突中の処理の登録
	m_collider->SetOnCollisionEnterCmd([this](Collider* other)
		{
			if (other->GetOwner()->GetTag() == ObjectTag::Stage)
			{
				SetIsGround(true);
			}
		});

	// 衝突終了時の処理の登録
	m_collider->SetOnCollisionExitCmd([this](Collider* other)
		{
			if (other->GetOwner()->GetTag() == ObjectTag::Stage)
			{
				SetIsGround(false);
			}
		});
}

void Ball::Initialize(SimpleMath::Vector3 position)
{
	m_transform->SetPosition(position);
	m_rigidBody->SetVelocity(SimpleMath::Vector3::Zero);
}

void Ball::Draw()
{
	m_transform->Rotate(m_angularVelocity);

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
	m_rigidBody->ApplyGravity();

	// 加速度の適用
	m_rigidBody->ApplyAccel();

	// 地上なら
	if(m_isGround)
		// 摩擦の適用
		m_rigidBody->ApplyFriction();

	// 速度を加算
	m_transform->Translate(m_rigidBody->GetVelocity() * TimeManager::Instance().GetElapsedTime());
}

void Ball::Rotate()
{
	// 速度の取得
	const SimpleMath::Vector3& velocity = m_rigidBody->GetVelocity();

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
		= velocity.Length() * TimeManager::Instance().GetElapsedTime() / m_collider->GetRadius();

	// 角速度を求める
	SimpleMath::Quaternion quaternion
		= SimpleMath::Quaternion::CreateFromAxisAngle(horizontalDirection, forwardAngle);

	// 角速度をマトリクスに変換
	m_angularVelocity = SimpleMath::Matrix::CreateFromQuaternion(quaternion);
}
