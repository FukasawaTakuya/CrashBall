/*****************************************************************//**
 * \file   Enemy.cpp
 * \brief  敵オブジェクトに関するソースファイル
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "Enemy.h"
#include "Game/State/Enemy/EnemyWanderState.h"
#include "Game/GameObject/Floor.h"
#include "Game/Common/MyMath.h"
#include "Game/Renderer/PrimitiveRendererManager.h"

// メンバ関数の定義 ===============================================================

/**
 * \brief コンストラクタ.
 * 
 * \param radius 半径
 */
Enemy::Enemy(float radius)
	: Ball(radius)
	, m_stateMachine{ std::make_unique<StateMachine<Enemy>>() }
{
	// ステートの生成
	m_stateMachine->CreateState<EnemyWanderState>();

	// ステートマシンの初期化
	m_stateMachine->Initialeze(this);

	// ステートの変更
	m_stateMachine->ChangeState<EnemyWanderState>();
}

/**
 * \brief デストラクタ.
 * 
 */
Enemy::~Enemy()
{
}

/**
 * \brief 初期化処理
 * 
 * \param position 初期位置
 */
void Enemy::Inisitialize(SimpleMath::Vector3 position)
{
	Ball::Initialize(position);
}

/**
 * \brief 更新処理.
 * 
 */
void Enemy::Update()
{
	RigidBody* rigidbody = GetComponent<RigidBody>();
	rigidbody->ResetAccel();

	if (m_stateMachine != nullptr)
		m_stateMachine->Update();

	// 地上にいるとき
	if (GetIsGround())
	{
		// 壁回避処理
		AvoidWall();
		// 進行方向を徐々に変える
		rigidbody->Accel(m_accelDirection * ACCELERATINON);
	}

	// 移動と回転
	Ball::Move();
	Ball::Rotate();

	// デバッグ用の方向ベクトル
	m_debugDirection = Slerp(m_debugDirection, m_accelDirection, 0.05f);

	// デバッグ用の線の描画
	VertexPositionNormalColor v[2]{
		VertexPositionNormalColor(GetComponent<Transform>()->GetPosition(), SimpleMath::Vector3::Up, Colors::Red),
		VertexPositionNormalColor(GetComponent<Transform>()->GetPosition() + m_debugDirection * 3.0f, SimpleMath::Vector3::Up, Colors::Red)
	};

	// 描画命令の登録
	PrimitiveRendererManager::Instance().RegisterDrawCommand({
		D3D10_PRIMITIVE_TOPOLOGY_LINELIST, std::vector<VertexPositionNormalColor>(std::begin(v), std::end(v))
		});
}

/**
 * \brief 描画処理.
 * 
 */
void Enemy::Draw()
{
	Ball::Draw();
}

/**
 * \brief 壁回避
 * 
 */
void Enemy::AvoidWall()
{
	// トランスフォームコンポーネントの取得
	Transform* transform = GetComponent<Transform>();

	// 壁のメッシュを取得
	auto& wallMesh = m_pFloor->GetWallMesh();

	for (auto wallFace : wallMesh)
	{
		// 壁との距離が一定以下のとき
		if ((wallFace->GetPlane()->CalcLength(transform->GetPosition()) <= AVOID_WALL_DISTANCE))
		{
			// 壁の法線ベクトルを水平方向に正規化して取得
			SimpleMath::Vector3 faceNormal = wallFace->GetPlane()->GetNormal();
			faceNormal.y = 0.0f;
			faceNormal.Normalize();

			// 壁の法線方向のベクトル
			SimpleMath::Vector3 vn = faceNormal.Dot(m_accelDirection) * faceNormal;
			// 
			SimpleMath::Vector3 vt = m_accelDirection - vn;

			// 壁の法線法線ベクトルを加算
			m_accelDirection = vt + faceNormal;
			m_accelDirection.Normalize();
			return;
		}
	}
}
