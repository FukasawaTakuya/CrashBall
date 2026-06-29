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
 * \brief コンストラクタ
 * 
 * \param data Jsonデータ
 */
Enemy::Enemy(json* data)
	:Ball(data)
{
	// コンポーネントの追加
	m_enemyController = AddComponent<EnemyController>((*data)["enemyController"]);
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
	GetComponent<Transform>()->SetPosition((*m_data)["transform"]["position"]);
	GetComponent<Rigidbody>()->SetVelocity(SimpleMath::Vector3::Zero);

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

/**
 * \brief パラメータ書き込み
 * 
 */
void Enemy::SaveParam()
{
	(*m_data)["enemyController"] = *m_enemyController;

	Ball::SaveParam();
}

/**
 * \brief 初期化用のパラメータの書き込み
 * 
 */
void Enemy::SaveInitParam()
{
	Ball::SaveInitParam();
}

/**
 * \brief データの再読み込み
 * 
 */
void Enemy::ReloadJson()
{
	*m_enemyController = (*m_data)["enemyController"];

	Ball::ReloadJson();
}
