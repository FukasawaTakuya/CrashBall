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

	// ステートの変更
	m_stateMachine->ChangeState<EnemyWanderState>();

	// トランスフォーム
	m_transform = GetGameObject()->GetComponent<Transform>();
	// 物理演算
	m_rigidbody = GetGameObject()->GetComponent<RigidBody>();
	// ボール管理
	m_ballController = GetGameObject()->GetComponent<BallController>();

}

EnemyController::~EnemyController()
{
}

void EnemyController::Update(const GameContext& gameContext)
{
	if (m_stateMachine != nullptr)
		m_stateMachine->Update();

	// 地上にいるとき
	if (m_ballController->GetIsGround())
	{
		// 壁回避処理
		AvoidWall();
		// 進行方向を徐々に変える
		m_rigidbody->Accel(m_accelDirection * ACCELERATINON);
	}
}

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
			if (direction.Dot(-faceNormal) > 0.0f)
			{
				m_rigidbody->Accel(faceNormal * 3.0f);
			}
			else
			{
				m_rigidbody->Accel(faceNormal * 0.7f);
			}
		}
	}

}
