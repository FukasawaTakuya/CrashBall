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

/**
 * \brief コンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 * \param pEnemyHpGauge 敵のHPゲージのポインタ
 * \param pEnemyHpText 敵のHP表示テキストのポインタ
 */
EnemyHpGaugeController::EnemyHpGaugeController(
	IGameObject* gameObject,
	IGameObject* pEnemyHpGauge,
	IGameObject* pEnemyHpGaugeTrack,
	IGameObject* pEnemyHpText)
	: Component(gameObject)
	, m_pEnemyHpGauge		(pEnemyHpGauge)
	, m_pEnemyHpGaugeTrack	(pEnemyHpGaugeTrack)
	, m_pEnemyHpText		(pEnemyHpText)
{
	// コンポーネントのキャッシュの取得
	m_enemyHpGaugeRenderer =
		m_pEnemyHpGauge->GetComponent<SpriteRenderer>();
	m_enemyHpTextRenderer =
		m_pEnemyHpText->GetComponent<TextRenderer>();
}

/**
 * \brief デストラクタ
 *
 */
EnemyHpGaugeController::~EnemyHpGaugeController()
{
}

/**
 * \brief 初期化
 *
 */
void EnemyHpGaugeController::Initialize()
{
	m_enemyHpGaugeRenderer->SetFillAmount(1.0f);
}

/**
 * \brief 更新
 *
 * \param gameConctext ゲーム用のコンテキスト
 */
void EnemyHpGaugeController::Update()
{
	// 切り取り量を求める
	float fillValue = static_cast<float>(m_enemyHp) / static_cast<float>(m_enemyMaxHp);

	// HPゲージをスライドさせる
	m_enemyHpGaugeRenderer->SetFillAmount(
		std::lerp(m_enemyHpGaugeRenderer->GetFillAmount(), fillValue, Time::GetElapsedTime() * GAUGE_SLIDE_SPEED));

	// 敵HPテキストの設定
	m_enemyHpTextRenderer->SetText(L"EnemyHP {} / {}", m_enemyHp, m_enemyMaxHp);
}

/**
 * \brief 終了処理
 *
 */
void EnemyHpGaugeController::Finalize()
{
}
