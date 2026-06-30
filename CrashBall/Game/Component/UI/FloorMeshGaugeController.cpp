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
