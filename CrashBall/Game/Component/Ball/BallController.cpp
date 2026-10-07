/*****************************************************************//**
 * \file   BallController.cpp
 * \brief  ボール操作コンポーネント
 *
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#include "pch.h"
#include "BallController.h"
#include "Game/Engine/Time.h"

using namespace DirectX;
RegisterComponent(BallController)

/**
 * \brief コンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 */
BallController::BallController(IGameObject* gameObject)
	: Component(gameObject)
{
}

/**
 * \brief デストラクタ
 * 
 */
BallController::~BallController()
{
}

/**
 * \brief アタッチ時の処理
 * 
 */
void BallController::Awake()
{
	// コンポーネントのキャッシュ
	m_transform = GetGameObject()->GetComponent<Transform>();
	m_rigidbody = GetGameObject()->GetComponent<Rigidbody>();
	m_sphereCollider = GetGameObject()->GetComponent<Sphere>();
	m_renderer = GetGameObject()->GetComponent<ModelRenderer>();

	// 衝突時の処理の登録
	m_sphereCollider->SetOnCollisionEnterCmd([this](Collider* other)
		{
			if (other->GetGameObject()->GetTag() == ObjectTag::Stage || 
				other->GetLayerMaskType() == LayerMaskType::Ball)
			{
				SetIsGround(true);
			}
		});

	// 衝突終了時の処理の登録
	m_sphereCollider->SetOnCollisionExitCmd([this](Collider* other)
		{
			if (m_sphereCollider->IsNoneCollideObject())
			{
				SetIsGround(false);
			}
		});
}

/**
 * \brief 開始処理
 *
 * \param gameContext ゲーム用のコンテキスト
 */
void BallController::Start(const GameContext& gameContext)
{
}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void BallController::Update(const GameContext& gameContext)
{
	// 地上なら
	if (m_isGround)
	{
		// 摩擦の適用
		m_rigidbody->ApplyFriction();

		// 回転を加算する
		AddRotate();
	}

	// 回転
	Rotate();
}

/**
 * \brief 描画
 * 
 * \param renderContext 描画用のコンテキスト
 */
void BallController::Render(const RenderContext& renderContext)
{
	// 描画管理クラスのインターフェース
	IModelRendererManager* rendererManager
		= renderContext.modelRendererManager;

	// 描画
	m_renderer->Render(renderContext);
}


/**
 * \brief 回転の加算
 * 
 */
void BallController::AddRotate()
{
	// 速度の取得
	const SimpleMath::Vector3& velocity = m_rigidbody->GetVelocity();

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


/**
 * \brief 回転
 * 
 */
void BallController::Rotate()
{
	m_angularVelocity = SimpleMath::Quaternion::Lerp(
		SimpleMath::Quaternion::Identity,
		m_angularVelocity,
		Time::GetTimeScale()
	);

	// 回転
	m_transform->Rotate(m_angularVelocity);
}
