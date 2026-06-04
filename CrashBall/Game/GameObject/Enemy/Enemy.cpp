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
 * \param RenderContext
 */
void Enemy::Render(const RenderContext& renderContext)
{
	Ball::Render(renderContext);

	renderContext.m_pTextRendererManager->RegisterRenderCommand(
		SimpleMath::Vector2(0.0f, 30.0f),
		Colors::White,
		1.0f,
		L"EnemyHp: {}", m_enemyController->GetHp()
	);
}

/**
 * \brief 終了処理
 * 
 */
void Enemy::Finalize()
{
}
