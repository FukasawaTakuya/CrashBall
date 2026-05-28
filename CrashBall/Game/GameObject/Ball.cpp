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
	m_rigidbody		 = AddComponent<RigidBody>(GRAVITY, FRICTION);
	m_sphereCollider = AddComponent<Sphere>(radius);
	m_renderer		 = AddComponent<ModelRenderer>();

	m_ballController = AddComponent<BallController>();
	m_ballController->Initialize();

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
				m_ballController->SetIsGround(true);
			}
		});

	// 衝突終了時の処理の登録
	m_sphereCollider->SetOnCollisionExitCmd([this](Collider* other)
		{
			if (other->GetOwner()->GetTag() == ObjectTag::Stage)
			{
				m_ballController->SetIsGround(false);
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
	m_ballController->Update(gameContext);
}

/**
 * \brief 描画
 * 
 */
void Ball::Render(const RenderContext& renderContext)
{
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

void Ball::SetPosition(DirectX::SimpleMath::Vector3 position)
{
	m_transform->SetPosition(position);
	m_rigidbody->SetVelocity(SimpleMath::Vector3::Zero);
}
