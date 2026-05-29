/*****************************************************************//**
 * \file   Enemy.cpp
 * \brief  敵クラス 
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#include "pch.h"
#include "Enemy.h"

using namespace DirectX;

/**
 * \brief コンストラクタ.
 * 
 * \param radius 半径
 */
Enemy::Enemy(float radius)
	: Ball(radius, ObjectTag::Enemy)
{
	m_enemyController = AddComponent<EnemyController>();
}

/**
 * \brief デストラクタ.
 * 
 */
Enemy::~Enemy()
{
}

/**
 * \brief 初期化
 * 
 * \param position 初期位置
 */
void Enemy::Initialize()
{
}

/**
 * \brief 更新
 * 
 */
void Enemy::Update(const GameContext& gameContext)
{
	//if (m_stateMachine != nullptr)
	//	m_stateMachine->Update();

	//// 地上にいるとき
	//if (GetIsGround())
	//{
	//	// 壁回避処理
	//	AvoidWall();
	//	// 進行方向を徐々に変える
	//	m_rigidbody->Accel(m_accelDirection * ACCELERATINON);
	//}

	m_enemyController->Update(gameContext);

	// 移動と回転
	Ball::Update(gameContext);
}

/**
 * \brief 描画
 * \param RenderContext
 */
void Enemy::Render(const RenderContext& renderContext)
{
	Ball::Render(renderContext);
}

/**
 * \brief 終了処理
 * 
 */
void Enemy::Finalize()
{
}
