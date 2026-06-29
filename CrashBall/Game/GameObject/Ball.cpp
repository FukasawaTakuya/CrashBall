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

#include "Game/Json/Enum/JsonEnumSerializers.h"

using namespace DirectX;


/**
 * \brief コンストラクタ
 * 
 * \param data
 */
Ball::Ball(json* data)
	: GameObject(data)
{
	if (!m_data->empty())
	{
		AddComponent<Transform>((*m_data)["transform"]);
		AddComponent<Rigidbody>((*m_data)["rigidbody"]);
		AddComponent<Sphere>((*m_data)["sphere"].get<Sphere>());
		AddComponent<ModelRenderer>((*m_data)["modelRenderer"]);
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

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void Ball::Update(const GameContext& gameContext)
{
	m_ballController->Update(gameContext);
}

/**
 * \brief 描画
 * 
 * \brief renderContext 描画用のコンテキスト
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

/**
 * \brief パラメータの書き込み
 * 
 */
void Ball::SaveParam()
{
	(*m_data)["ObjectTag"]		=  GetTag();
	(*m_data)["rigidbody"]		= *GetComponent<Rigidbody>();
	(*m_data)["sphere"]			= *GetComponent<Sphere>();
	(*m_data)["modelRenderer"]	= *GetComponent<ModelRenderer>();

	Transform* transform = GetComponent<Transform>();
	(*m_data)["transform"]["rotate"] = transform->GetLocalRotate();
	(*m_data)["transform"]["scale"] = transform->GetLocalScale();
}

/**
 * \brief 初期化用のパラメータの書き込み
 * 
 */
void Ball::SaveInitParam()
{
	(*m_data)["transform"]		= *GetComponent<Transform>();
	(*m_data)["rigidbody"]		= *GetComponent<Rigidbody>();
	(*m_data)["sphere"]			= *GetComponent<Sphere>();
	(*m_data)["modelRenderer"]	= *GetComponent<ModelRenderer>();
}

/**
 * \brief Jsonの再読み込み
 * 
 */
void Ball::ReloadJson()
{
	*GetComponent<Transform>() = (*m_data)["transform"];
	*GetComponent<Rigidbody>() = (*m_data)["rigidbody"];
	*GetComponent<Sphere>()		= (*m_data)["sphere"];
	*GetComponent<ModelRenderer>() = (*m_data)["modelRenderer"];
	
	SetTag((*m_data)["ObjectTag"]);
}
