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

/**
 * \brief コンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 */
BallController::BallController(IGameObject* gameObject)
	: Component(gameObject)
{
	// コンポーネントのキャッシュ
	m_transform			= GetGameObject()->GetComponent<Transform>();
	m_rigidbody			= GetGameObject()->GetComponent<RigidBody>();
	m_sphereCollider	= GetGameObject()->GetComponent<Sphere>();
	m_renderer			= GetGameObject()->GetComponent<ModelRenderer>();

	// レイヤーマスクの設定
	m_sphereCollider->SetLayerMask(LayerMask::Ball);

	// スケールの設定
	m_transform->SetScale(SCALE);

	// 衝突時の処理の登録
	m_sphereCollider->SetOnCollisionEnterCmd([this](Collider* other)
		{
			if (other->GetGameObject()->GetTag() == ObjectTag::Stage)
			{
				SetIsGround(true);
			}
		});

	// 衝突終了時の処理の登録
	m_sphereCollider->SetOnCollisionExitCmd([this](Collider* other)
		{
			if (other->GetGameObject()->GetTag() == ObjectTag::Stage)
			{
				SetIsGround(false);
			}
		});
}

/**
 * \brief デストラクタ
 * 
 */
BallController::~BallController()
{
}

/**
 * \brief 初期化
 * 
 */
void BallController::Initialize()
{
}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void BallController::Update(const GameContext& gameContext)
{
	// 移動
	Move();

	// 地上なら回転を加算する
	if (m_isGround)
	{
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
	m_renderer->Render(rendererManager, m_transform->GetWorld());
}


/**
 * \brief 終了処理
 * 
 */
void BallController::Finalize()
{
}


/**
 * \brief 移動
 * 
 */
void BallController::Move()
{
	// 重力の適用
	m_rigidbody->ApplyGravity();

	// 加速度の適用
	m_rigidbody->ApplyAccel();

	// 地上なら
	if (m_isGround)
		// 摩擦の適用
		m_rigidbody->ApplyFriction();

	// 速度を加算
	m_transform->Translate(m_rigidbody->GetVelocity() * Time::GetElapsedTime());

	// 加速度のリセット
	m_rigidbody->ResetAccel();
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
	// 回転
	m_transform->Rotate(m_angularVelocity);
}
