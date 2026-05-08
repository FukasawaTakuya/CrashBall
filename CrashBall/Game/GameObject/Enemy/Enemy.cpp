#include "pch.h"
#include "Enemy.h"
#include "Game/State/Enemy/EnemyWanderState.h"

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

void Enemy::Inisitialize(SimpleMath::Vector3 position)
{
	Ball::Initialize(position);
	m_direction = SimpleMath::Vector3::Forward;
}

/**
 * \brief 更新処理.
 * 
 */
void Enemy::Update()
{
	if (m_stateMachine != nullptr)
		m_stateMachine->Update();

	RigidBody* rigidBody = GetComponent<RigidBody>();

	rigidBody->SetVelocity({m_direction.x * 5.0f, rigidBody->GetVelocity().y, m_direction.z * 5.0f});

	SimpleMath::Vector3 velocity = rigidBody->GetVelocity();

	m_direction = XMVector3Normalize({ velocity.x, 0.0f, velocity.z });

	Ball::Move();

	Ball::Rotate();
}

/**
 * \brief 描画処理.
 * 
 */
void Enemy::Draw()
{
	Ball::Draw();
}
