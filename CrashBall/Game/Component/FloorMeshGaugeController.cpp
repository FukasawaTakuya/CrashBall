#include "pch.h"
#include "FloorMeshGaugeController.h"
#include "Game/Engine/Time.h"
#include "Game/Color/GameColor.h"


using namespace DirectX;

FloorMeshGaugeController::FloorMeshGaugeController(
	IGameObject* gameObject, 
	IGameObject* pPalyerMeshGauge, 
	IGameObject* pEnemyMeshGauge, 
	IGameObject* pGaugeTrack,
	IGameObject* pGaugeBackGround, 
	IGameObject* pPlayerMeshNumText, 
	IGameObject* pEnemyMeshNumText)
	: Component(gameObject)
	, m_pPalyerMeshGauge(pPalyerMeshGauge)
	, m_pEnemyMeshGauge(pEnemyMeshGauge)
	, m_pGaugeTrack(pGaugeTrack)
	, m_pGaugeBackGround(pGaugeBackGround)
	, m_pPlayerMeshNumText(pPlayerMeshNumText)
	, m_pEnemyMeshNumText(pEnemyMeshNumText)
{
	// ゲージのコンポーネントのキャッシュの取得
	m_playerGaugeRenderer = m_pPalyerMeshGauge->GetComponent<SpriteRenderer>();
	m_playerGaugeTransform = m_pPalyerMeshGauge->GetComponent<RectTransform>();
	m_enemyGaugeRenderer = m_pEnemyMeshGauge->GetComponent<SpriteRenderer>();
	m_enemyGaugeTransform = m_pEnemyMeshGauge->GetComponent<RectTransform>();
	// テキストのコンポーネントのキャッシュの取得
	m_playerTextRenderer = pPlayerMeshNumText->GetComponent<TextRenderer>();
	m_enemyTextRenderer = pEnemyMeshNumText->GetComponent<TextRenderer>();
	// ゲージの土台のコンポーネントのキャッシュ
	m_gaugeTrackRenderer = m_pGaugeTrack->GetComponent<SpriteRenderer>();
	m_gaugeTrackTransform = m_pGaugeTrack->GetComponent<RectTransform>();

	// -------------- ゲージの土台 -------------- //
	// 描画位置
	m_gaugeTrackTransform->SetPosition(GAUGE_POSITION);
	// 基準位置
	m_gaugeTrackTransform->SetOrigin(Origin::Center);
	// 描画順
	m_gaugeTrackRenderer->SetLayerDepth(0.1f);

	// -------------- 背景 -------------- //
	// 描画コンポーネント
	SpriteRenderer* backGroundRenderer
		= m_pGaugeBackGround->GetComponent<SpriteRenderer>();
	// スケール
	backGroundRenderer->SetSpriteScale(SimpleMath::Vector2(1.1f, 3.5f));
	// 色
	backGroundRenderer->SetColor({ 0.0f, 0.0f, 0.0f, 0.4f });
	// 描画位置
	m_pGaugeBackGround->GetComponent<RectTransform>()->SetPosition({ Screen::CENTER_X, Screen::HEIGHT - 55.f });

	// -------------- ゲージ -------------- //
	// 描画順
	m_playerGaugeRenderer->SetLayerDepth(GAUGE_LAYER_DEPTH);
	m_enemyGaugeRenderer->SetLayerDepth(GAUGE_LAYER_DEPTH);
	// ゲージの色
	m_playerGaugeRenderer->SetColor(GameColor::PLAYER);
	m_enemyGaugeRenderer->SetColor(GameColor::ENEMY);
	// 基準位置
	m_playerGaugeTransform->SetOrigin(Origin::LeftCenter);
	m_enemyGaugeTransform->SetOrigin(Origin::LeftCenter);
	m_enemyGaugeTransform->SetOrigin(Origin::RightCenter);
	// 切り取りの起点
	m_enemyGaugeRenderer->SetFillOrigin(FillOrigin::Right);

	// -------------- テキスト -------------- //
	RectTransform* playerTextTransform = m_pPlayerMeshNumText->GetComponent<RectTransform>();
	RectTransform* enemyTextTransform = m_pEnemyMeshNumText->GetComponent<RectTransform>();
	// 描画位置
	playerTextTransform->SetPosition({ Screen::CENTER_X - 250.0f, Screen::HEIGHT - 95.0f });
	enemyTextTransform->SetPosition({ Screen::CENTER_X + 250.0f, Screen::HEIGHT - 95.0f });
	// テキストの色
	m_playerTextRenderer->SetColor(GameColor::PLAYER);
	m_enemyTextRenderer->SetColor(GameColor::ENEMY);
	// フォントのスケール
	m_playerTextRenderer->SetFontScale(0.75f);
	m_enemyTextRenderer->SetFontScale(0.75f);
}

/**
 * \brief デストラクタ
 * 
 */
FloorMeshGaugeController::~FloorMeshGaugeController()
{
}

/**
 * \brief 初期化
 * 
 */
void FloorMeshGaugeController::Initialize()
{
	// 切り取り量の設定
	m_playerGaugeRenderer->SetFillAmount(0.0f);
	m_enemyGaugeRenderer->SetFillAmount(0.0f);

	// 描画位置の設定
	m_playerGaugeTransform
		->SetPosition({ m_gaugeTrackTransform->GetLeft(m_gaugeTrackRenderer->GetWidth()), GAUGE_POSITION.y });
	m_enemyGaugeTransform
		->SetPosition({ m_playerGaugeTransform->GetRight(m_playerGaugeRenderer->GetWidth()), GAUGE_POSITION.y });

	m_enemyGaugeTransform
		->SetPosition({ m_gaugeTrackTransform->GetRight(m_gaugeTrackRenderer->GetWidth()), GAUGE_POSITION.y });

}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void FloorMeshGaugeController::Update()
{
	// 全体の面に対する塗った面の割合
	float playerFillAmount = static_cast<float>(m_playerMeshCount) / static_cast<float>(m_totalMeshCount);
	float enemyFillAmount = static_cast<float>(m_enemyMeshCount) / static_cast<float>(m_totalMeshCount);

	// ゲージをスライドさせる
	playerFillAmount = std::lerp(m_playerGaugeRenderer->GetFillAmount(), playerFillAmount, Time::GetElapsedTime() * 5.0f);
	enemyFillAmount = std::lerp(m_enemyGaugeRenderer->GetFillAmount(), enemyFillAmount, Time::GetElapsedTime() * 5.0f);

	// 切り取り量の設定
	m_playerGaugeRenderer->SetFillAmount(playerFillAmount);
	m_enemyGaugeRenderer->SetFillAmount(enemyFillAmount);

	// 敵のバーの位置を設定
	//m_enemyGaugeTransform
	//	->SetPosition({ m_playerGaugeTransform->GetRight(m_playerGaugeRenderer->GetWidth()), GAUGE_POSITION.y });

	// テキストの設定
	m_playerTextRenderer->SetText(L"Player:{}面", m_playerMeshCount);
	m_enemyTextRenderer->SetText(L"Enemy:{}面", m_enemyMeshCount);
}

/**
 * \brief 終了処理
 * 
 */
void FloorMeshGaugeController::Finalize()
{
}
