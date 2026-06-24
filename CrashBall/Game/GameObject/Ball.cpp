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

#include "Game/Json/JsonDeserializers.h"
#include "Game/Json/JsonSerializers.h"

using namespace DirectX;

Ball::Ball(float radius, ObjectTag tag)
	: GameObject(tag)
{
	// コンポーネントの追加
	AddComponent<Transform>();
	AddComponent<Rigidbody>(GRAVITY, FRICTION);
	AddComponent<Sphere>(radius);
	AddComponent<ModelRenderer>();

	// ボール操作コンポーネントのキャッシュ
	m_ballController = AddComponent<BallController>();
}

Ball::Ball(json* data, ObjectTag tag)
	: GameObject(tag)
{
	m_data = data;

	if (!m_data->empty())
	{
		AddComponent<Transform>((*m_data)["transform"]);
		AddComponent<Rigidbody>((*m_data)["rigidbody"]);
		AddComponent<Sphere>((*m_data)["sphere"].get<Sphere>());
		AddComponent<ModelRenderer>((*m_data)["modelRenderer"]);
	}
	else
	{
		AddComponent<Transform>();
		AddComponent<Rigidbody>(GRAVITY, FRICTION);
		AddComponent<Sphere>(20.0f);
		AddComponent<ModelRenderer>();
	}

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

void Ball::SaveJson()
{
	(*m_data)["transform"] = *GetComponent<Transform>();
	(*m_data)["rigidbody"] = *GetComponent<Rigidbody>();
	(*m_data)["sphere"] = *GetComponent<Sphere>();
	(*m_data)["modelRenderer"] = *GetComponent<ModelRenderer>();
}

void Ball::ReloadJson()
{
	SimpleMath::Vector3 vec3 = (*m_data)["transform"]["scale"];

	GetComponent<Transform>()->SetScale(
		vec3
		);
}
