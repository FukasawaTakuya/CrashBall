/*****************************************************************//**
 * \file   Enemy.cpp
 * \brief  敵クラス 
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#include "pch.h"
#include "Enemy.h"
#include <Game/Common/Screen.h>

using namespace DirectX;

/**
 * \brief コンストラクタ.
 * 
 * \param radius 半径
 */
Enemy::Enemy()
	: Ball(RADIUS, ObjectTag::Enemy)
{
	m_enemyController = AddComponent<EnemyController>();

	GetComponent<Transform>()->SetScale(SCALE);
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
	m_enemyController->Initialize();
}

/**
 * \brief 更新
 * 
 */
void Enemy::Update(const GameContext& gameContext)
{
	m_enemyController->Update(gameContext);

	// 移動と回転
	Ball::Update(gameContext);
}

/**
 * \brief 描画
 * \param RenderContext 描画用のコンテキスト
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
