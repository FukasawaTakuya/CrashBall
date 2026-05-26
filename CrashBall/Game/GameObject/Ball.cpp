/*****************************************************************//**
 * \file   Ball.cpp
 * \brief  ボールクラス 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#include "pch.h"
#include "Ball.h"
#include "Game/Engine/Time.h"

using namespace DirectX;

Ball::Ball(float radius, ObjectTag tag)
	: GameObject(tag)
{
	// コンポーネントの追加
	m_transform		 = AddComponent<Transform>();
	m_rigidBody		 = AddComponent<RigidBody>(GRAVITY, FRICTION);
	m_sphereCollider = AddComponent<Sphere>(radius);
	m_renderer		 = AddComponent<ModelRenderer>();

	// トランスフォームの設定
	m_sphereCollider->SetTransform(m_transform);
	// レイヤーマスクの設定
	m_sphereCollider->SetLayerMask(LayerMask::Ball);

	// スケールの設定
	m_transform->SetScale(0.025f);

	// 衝突中の処理の登録
	m_sphereCollider->SetOnCollisionEnterCmd([this](Collider* other)
		{
			if (other->GetOwner()->GetTag() == ObjectTag::Stage)
			{
				SetIsGround(true);
			}
		});

	// 衝突終了時の処理の登録
	m_sphereCollider->SetOnCollisionExitCmd([this](Collider* other)
		{
			if (other->GetOwner()->GetTag() == ObjectTag::Stage)
			{
				SetIsGround(false);
			}
		});
}

/**
 * \brief 初期化
 * 
 * \param position 初期位置
 */
void Ball::Initialize()
{
}

void Ball::Update(const GameContext& gameContext)
{
}

/**
 * \brief 描画
 * 
 */
void Ball::Render(const RenderContext& renderContext)
{
	// 回転
	m_transform->Rotate(m_angularVelocity);

	// 描画管理クラスのインターフェース
	IModelRendererManager* rendererManager
		= renderContext.m_pModelRendererManager;

	// 描画
	m_renderer->Render(rendererManager, m_transform->GetWorld());
}


/**
 * \brief 終了処理
 * 
 * \param RenderContext
 */
void Ball::Finalize()
{
}

/**
 * \brief 移動
 * 
 */
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
	m_transform->Translate(m_rigidBody->GetVelocity() * Time::GetElapsedTime());
}

/**
 * \brief 回転
 * 
 */
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
		= velocity.Length() * Time::GetElapsedTime() / m_sphereCollider->GetRadius();

	// 角速度を求める
	SimpleMath::Quaternion quaternion
		= SimpleMath::Quaternion::CreateFromAxisAngle(horizontalDirection, forwardAngle);
	m_angularVelocity = quaternion;
}

void Ball::SetPosition(DirectX::SimpleMath::Vector3 position)
{
	m_transform->SetPosition(position);
	m_rigidBody->SetVelocity(SimpleMath::Vector3::Zero);
}
