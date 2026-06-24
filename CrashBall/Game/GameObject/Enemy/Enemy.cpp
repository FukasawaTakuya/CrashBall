/*****************************************************************//**
 * \file   Enemy.cpp
 * \brief  敵クラス 
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#include "pch.h"
#include "Enemy.h"

#include "Game/Json/JsonDeserializers.h"
#include "Game/Json/JsonSerializers.h"

using namespace DirectX;

/**
 * \brief コンストラクタ.
 * 
 * \param radius 半径
 */
Enemy::Enemy()
	: Ball(RADIUS, ObjectTag::Enemy)
{
	// コンポーネントの追加
	m_enemyController = AddComponent<EnemyController>();

	// スケールの設定
	GetComponent<Transform>()->SetScale(SCALE);
}

Enemy::Enemy(json* data)
	:Ball(data)
{
	// コンポーネントの追加
	m_enemyController = AddComponent<EnemyController>();

	// スケールの設定
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
