#include "pch.h"
#include "EnemyHpGaugeController.h"
#include "Game/Engine/Time.h"
#include "Game/Color/GameColor.h"

using namespace DirectX;

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
	SpriteRenderer* enemyHpGaugeTrackRenderer =
		m_pEnemyHpGaugeTrack->GetComponent<SpriteRenderer>();

	// 描画位置の設定
	m_pEnemyHpGauge->GetComponent<RectTransform>()
		->SetPosition(ENEMY_HP_POSITION);
	m_pEnemyHpGaugeTrack->GetComponent<RectTransform>()
		->SetPosition(ENEMY_HP_POSITION);
	m_pEnemyHpText->GetComponent<RectTransform>()
		->SetPosition(ENEMY_HP_TEXT_POSITION);

	// 色の設定
	m_enemyHpGaugeRenderer->SetColor(GameColor::ENEMY);
	enemyHpGaugeTrackRenderer->SetColor(Colors::Black);

	// スケール
	m_enemyHpTextRenderer->SetFontScale(0.5f);
	m_enemyHpGaugeRenderer->SetSpriteScale(0.8f);
	enemyHpGaugeTrackRenderer->SetSpriteScale(0.8f);

	// 描画順
	m_enemyHpGaugeRenderer->SetLayerDepth(0.1f);
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
		std::lerp(m_enemyHpGaugeRenderer->GetFillAmount(), fillValue, Time::GetElapsedTime() * 5.0f));

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
