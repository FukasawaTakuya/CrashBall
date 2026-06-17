#include "pch.h"
#include "EnemyController.h"
#include "Game/State/Enemy/EnemyWanderState.h"

EnemyController::EnemyController(IGameObject* gameObject)
	: Component(gameObject)
	, m_stateMachine{ std::make_unique<StateMachine<EnemyController>>(this) }
{
	// 敵ステート用のコンテキスト
	EnemyStateContext stateContext{
			GetGameObject()->GetComponent<Transform>(),
			GetGameObject()->GetComponent<RigidBody>()
	};

	// ステートの生成
	m_stateMachine->CreateState<EnemyWanderState>(stateContext);

	// 初期ステートの設定
	m_stateMachine->ChangeState<EnemyWanderState>();

	// コンポーネントのキャッシュ
	m_transform = GetGameObject()->GetComponent<Transform>();
	m_rigidbody = GetGameObject()->GetComponent<RigidBody>();
	m_modelRenderer = GetGameObject()->GetComponent<ModelRenderer>();
	m_ballController = GetGameObject()->GetComponent<BallController>();
}

/**
 * \brief デストラクタ
 * 
 */
EnemyController::~EnemyController()
{
}

/**
 * \brief 初期化
 * 
 */
void EnemyController::Initialize()
{
	m_hp = MAX_HP;
}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void EnemyController::Update(const GameContext& gameContext)
{
	// ステートの更新
	if (m_stateMachine != nullptr)
		m_stateMachine->Update();

	// 地上にいるとき
	if (m_ballController->GetIsGround())
	{
		// 壁回避
		AvoidWall();
		// 加速
		m_rigidbody->Accel(m_accelDirection * ACCELERATINON);
	}
}

/**
 * \brief ダメージ処理
 * 
 * \param damage ダメージ
 */
void EnemyController::Damage(float damage)
{
	m_hp = std::clamp(m_hp - damage, 0.0f, MAX_HP);
}

/**
 * \brief 壁回避
 * 
 */
void EnemyController::AvoidWall()
{
	// 壁のメッシュを取得
	auto& wallMesh = m_wallMeshGetter->GetWallMesh();

	for (auto& wallFace : wallMesh)
	{
		// 壁との距離が一定以下のとき
		if ((wallFace->GetPlane()->CalcLength(m_transform->GetPosition()) <= AVOID_WALL_DISTANCE))
		{
			// 壁の法線ベクトルを水平方向に正規化して取得
			SimpleMath::Vector3 faceNormal = wallFace->GetPlane()->GetNormal();
			faceNormal.y = 0.0f;
			faceNormal.Normalize();

			// 加速方向と壁の方向が同じなら加速方向を補正
			if (m_accelDirection.Dot(-faceNormal) > 0.0f)
			{
				// 加速方向の壁の法線方向のベクトル成分
				SimpleMath::Vector3 vn = faceNormal.Dot(m_accelDirection) * faceNormal;
				// 接線ベクトルを求める
				SimpleMath::Vector3 vt = m_accelDirection - vn;

				// 加速方向に接線ベクトルを設定
				m_accelDirection = vt;
				m_accelDirection.Normalize();
			}

			// 進行方向
			SimpleMath::Vector3 direction = XMVector3Normalize(m_rigidbody->GetVelocity());
			// 進行方向と壁の方向が同じなら強い力で速度を補正
			if (direction.Dot(-faceNormal) > 0.0f)
			{
				m_rigidbody->Accel(faceNormal * 3.0f);
			}
			// 弱い力で速度を補正
			else
			{
				m_rigidbody->Accel(faceNormal * 0.7f);
			}
		}
	}

}
