/*****************************************************************//**
 * \file   FloorMeshGaugeController.cpp
 * \brief  床メッシュゲージ操作コンポーネント
 *
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/
#include "pch.h"
#include "FloorMeshGaugeController.h"
#include "Game/Engine/Time.h"
#include "Game/Color/GameColor.h"

using namespace DirectX;


/**
 * \brief コンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 * \param pPalyerMeshGauge プレイヤーのメッシュゲージのポインタ
 * \param pEnemyMeshGauge 敵のメッシュゲージのポインタ
 * \param pGaugeTrack ゲージの土台のポインタ
 * \param pGaugeBackGround ゲージの背景のポインタ
 * \param pPlayerMeshNumText プレイヤーのメッシュ数表示テキストのポインタ
 * \param pEnemyMeshNumText 敵のメッシュ数表示テキストのポインタ
 */
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
	m_playerGaugeRenderer	= m_pPalyerMeshGauge->GetComponent<SpriteRenderer>();
	m_playerGaugeTransform	= m_pPalyerMeshGauge->GetComponent<RectTransform>();
	m_enemyGaugeRenderer	= m_pEnemyMeshGauge->GetComponent<SpriteRenderer>();
	m_enemyGaugeTransform	= m_pEnemyMeshGauge->GetComponent<RectTransform>();
	// テキストのコンポーネントのキャッシュの取得
	m_playerTextRenderer	= pPlayerMeshNumText->GetComponent<TextRenderer>();
	m_enemyTextRenderer		= pEnemyMeshNumText->GetComponent<TextRenderer>();
	// ゲージの土台のコンポーネントのキャッシュ
	m_gaugeTrackRenderer	= m_pGaugeTrack->GetComponent<SpriteRenderer>();
	m_gaugeTrackTransform	= m_pGaugeTrack->GetComponent<RectTransform>();

	// -------------- ゲージの土台 -------------- //
	// 描画位置
	m_gaugeTrackTransform->SetPosition(GAUGE_POSITION);
	// 基準位置
	m_gaugeTrackTransform->SetOrigin(Origin::Center);
	// 描画順
	m_gaugeTrackRenderer->SetLayerDepth(TRACK_LAYER_DEPTH);

	// -------------- 背景 -------------- //
	// 描画コンポーネント
	SpriteRenderer* backGroundRenderer
		= m_pGaugeBackGround->GetComponent<SpriteRenderer>();
	// スケール
	backGroundRenderer->SetSpriteScale(BACKGROUND_SCALE);
	// 色
	backGroundRenderer->SetColor(GameColor::MESH_GAUGE_BACKGROUND);
	// 描画位置
	m_pGaugeBackGround->GetComponent<RectTransform>()->SetPosition(GAUGE_POSITION);

	// -------------- ゲージ -------------- //
	// 描画順
	m_playerGaugeRenderer->SetLayerDepth(GAUGE_LAYER_DEPTH);
	m_enemyGaugeRenderer->SetLayerDepth(GAUGE_LAYER_DEPTH);
	// ゲージの色
	m_playerGaugeRenderer->SetColor(GameColor::PLAYER);
	m_enemyGaugeRenderer->SetColor(GameColor::ENEMY);
	// 描画位置
	m_playerGaugeTransform->SetPosition(GAUGE_POSITION);
	m_enemyGaugeTransform->SetPosition(GAUGE_POSITION);
	// 切り取りの起点
	m_enemyGaugeRenderer->SetFillOrigin(FillOrigin::Right);

	// -------------- テキスト -------------- //
	RectTransform* playerTextTransform = m_pPlayerMeshNumText->GetComponent<RectTransform>();
	RectTransform* enemyTextTransform  = m_pEnemyMeshNumText->GetComponent<RectTransform>();
	// 描画位置
	playerTextTransform->SetPosition(PLAYER_MESHTEXT_POSITION);
	enemyTextTransform->SetPosition(ENEMY_MESHTEXT_POSITION);
	// 描画順
	m_playerTextRenderer->SetLayerDepth(TEXT_LAYER_DEPTH);
	m_enemyTextRenderer->SetLayerDepth(TEXT_LAYER_DEPTH);
	// テキストの色
	m_playerTextRenderer->SetColor(GameColor::PLAYER);
	m_enemyTextRenderer->SetColor(GameColor::ENEMY);
	// フォントのスケール
	m_playerTextRenderer->SetFontScale(TEXT_FONTSCALE);
	m_enemyTextRenderer->SetFontScale(TEXT_FONTSCALE);
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
	playerFillAmount = std::lerp(m_playerGaugeRenderer->GetFillAmount(), playerFillAmount, Time::GetElapsedTime() * GAUGE_SLIDE_SPEED);
	enemyFillAmount = std::lerp(m_enemyGaugeRenderer->GetFillAmount(), enemyFillAmount, Time::GetElapsedTime() * GAUGE_SLIDE_SPEED);

	// 切り取り量の設定
	m_playerGaugeRenderer->SetFillAmount(playerFillAmount);
	m_enemyGaugeRenderer->SetFillAmount(enemyFillAmount);

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
