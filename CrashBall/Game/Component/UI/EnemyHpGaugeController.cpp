/*****************************************************************//**
 * \file   EnemyHpGaugeController.cpp
 * \brief  敵HPゲージ操作コンポーネント
 *
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/


#include "pch.h"
#include "EnemyHpGaugeController.h"
#include "Game/Engine/Time.h"
#include "Game/Color/GameColor.h"

using namespace DirectX;
RegisterComponent(EnemyHpGaugeController)

/**
 * \brief コンストラクタ
 *
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 */
EnemyHpGaugeController::EnemyHpGaugeController(IGameObject* gameObject)
	: Component(gameObject)
{
}

/**
 * \brief デストラクタ
 *
 */
EnemyHpGaugeController::~EnemyHpGaugeController()
{
}

/**
 * \brief アタッチ時の処理
 * 
 */
void EnemyHpGaugeController::Awake()
{
	// コンポーネントのキャッシュの取得
	m_enemyHpGaugeController =
		m_pEnemyHpGauge->GetComponent<SliderController>();
	m_enemyHpTextRenderer =
		m_pEnemyHpText->GetComponent<TextRenderer>();

}

/**
 * \brief 初期化
 *
 */
void EnemyHpGaugeController::Start(const GameContext& gameContext)
{
	m_enemyHpGaugeController->SetCurrentAmount(1.0f);
}

/**
 * \brief 更新
 *
 * \param gameConctext ゲーム用のコンテキスト
 */
void EnemyHpGaugeController::Update(const GameContext& gameContext)
{
	int enemyHp = m_pEnemyController->GetHp();		// 敵のHP
	int enemyMaxHp = m_pEnemyController->GetMaxHP();	// 敵の最大HP


	// 切り取り量を求める
	float fillValue = static_cast<float>(enemyHp) / static_cast<float>(enemyMaxHp);

	// 目標値の設定
	m_enemyHpGaugeController->SetTargetAmount(fillValue);
	// スライド
	m_enemyHpGaugeController->Slide();

	// 敵HPテキストの設定
	m_enemyHpTextRenderer->SetText(L"EnemyHP {} / {}", enemyHp, enemyMaxHp);
}

/**
 * \brief 終了処理
 *
 */
void EnemyHpGaugeController::Finalize()
{
}
