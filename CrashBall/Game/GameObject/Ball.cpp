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
	AddComponent<Transform>();
	AddComponent<RigidBody>(GRAVITY, FRICTION);
	AddComponent<Sphere>(radius);
	AddComponent<ModelRenderer>();

	// ボール操作コンポーネントのキャッシュ
	m_ballController = AddComponent<BallController>();
}

/**
 * \brief 初期化
 * 
 */
void Ball::Initialize()
{
	m_ballController->Initialize();
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
	m_ballController->Render(renderContext);
}


/**
 * \brief 終了処理
 * 
 */
void Ball::Finalize()
{
	m_ballController->Finalize();
}

void Ball::SetPosition(DirectX::SimpleMath::Vector3 position)
{
	GetComponent<Transform>()->SetPosition(position);
	GetComponent<RigidBody>()->SetVelocity(SimpleMath::Vector3::Zero);
}
