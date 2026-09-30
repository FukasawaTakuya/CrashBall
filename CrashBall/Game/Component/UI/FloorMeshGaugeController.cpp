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

RegisterComponent(FloorMeshGaugeController)


/**
 * \brief コンストラクタ
 *
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 */
FloorMeshGaugeController::FloorMeshGaugeController(IGameObject* gameObject)
	: Component(gameObject)
{
}


/**
 * \brief アタッチ時の処理
 * 
 */
void FloorMeshGaugeController::Awake()
{
	// ゲージのコンポーネントのキャッシュの取得
	m_playerGaugeController = m_pPalyerMeshGauge->GetComponent<SliderController>();
	m_enemyGaugeController = m_pEnemyMeshGauge->GetComponent<SliderController>();
	// テキストのコンポーネントのキャッシュの取得
	m_playerTextRenderer = m_pPlayerMeshNumText->GetComponent<TextRenderer>();
	m_enemyTextRenderer = m_pEnemyMeshNumText->GetComponent<TextRenderer>();
}

/**
 * \brief 開始処理
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void FloorMeshGaugeController::Start(const GameContext& gameContext)
{
	// 切り取り量の設定
	m_playerGaugeController->SetCurrentAmount(0.0f);
	m_enemyGaugeController->SetCurrentAmount(0.0f);

	// テキストの設定
	m_playerTextRenderer->SetText(L"Player:0面");
	m_enemyTextRenderer->SetText(L"Enemy:0面");
}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void FloorMeshGaugeController::Update(const GameContext& gameContext)
{

	int playerMeshCount = m_pStageController->GetPlayerMeshCount();	// プレイヤーの面の数
	int enemyMeshCount = m_pStageController->GetEnemyMeshCount();	// 敵の面の数
	int totalMeshCount = m_pStageController->GetTotalMeshCount();	// 全体の面の数

	// 全体の面に対する塗った面の割合
	float playerFillAmount = static_cast<float>(playerMeshCount) / static_cast<float>(totalMeshCount);
	float enemyFillAmount = static_cast<float>(enemyMeshCount) / static_cast<float>(totalMeshCount);

	// 目標値の設定
	m_enemyGaugeController->SetTargetAmount(enemyFillAmount);
	m_playerGaugeController->SetTargetAmount(playerFillAmount);
	// スライド
	m_enemyGaugeController->Slide();
	m_playerGaugeController->Slide();

	// テキストの設定
	m_playerTextRenderer->SetText(L"Player:{}面", playerMeshCount);
	m_enemyTextRenderer->SetText(L"Enemy:{}面", enemyMeshCount);
}

