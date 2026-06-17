#include "pch.h"
#include "EnemyHpGaugeController.h"
#include "Game/Engine/Time.h"

/**
 * \brief コンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 * \param pEnemyHpGauge 敵のHPゲージ
 * \param pEnemyHpText 敵のHP表示テキスト
 */
EnemyHpGaugeController::EnemyHpGaugeController(
	IGameObject* gameObject,
	IGameObject* pEnemyHpGauge,
	IGameObject* pEnemyHpText)
	: Component(gameObject)
	, m_pEnemyHpGauge(pEnemyHpGauge)
	, m_pEnemyHpText(pEnemyHpText)
{
	// コンポーネントのキャッシュの取得
	m_enemyHpGaugeRenderer =
		m_pEnemyHpGauge->GetComponent<SpriteRenderer>();
	m_enemyHpTextRenderer =
		m_pEnemyHpText->GetComponent<TextRenderer>();

	// 描画位置の設定
	m_pEnemyHpGauge->GetComponent<RectTransform>()
		->SetPosition(ENEMY_HP_POSITION);
	m_pEnemyHpText->GetComponent<RectTransform>()
		->SetPosition(ENEMY_HP_TEXT_POSITION);
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
	m_enemyHpGaugeRenderer->SetFillAmount(0.0f);
}

/**
 * \brief 更新
 *
 * \param gameConctext ゲーム用のコンテキスト
 */
void EnemyHpGaugeController::Update(const GameContext& gameConctext)
{
	float fillValue = static_cast<float>(m_enemyHp) / static_cast<float>(m_enemyMaxHp);

	//m_enemyHpGaugeRenderer->SetFillAmount(
	//	std::lerp(m_enemyHpGaugeRenderer->GetFillAmount(), fillValue, Time::GetElapsedTime() * 5.0f));

	m_enemyHpTextRenderer->SetText(L"EnemyHP {} / {}", m_enemyHp, m_enemyMaxHp);
}

/**
 * \brief 終了処理
 *
 */
void EnemyHpGaugeController::Finalize()
{
}
