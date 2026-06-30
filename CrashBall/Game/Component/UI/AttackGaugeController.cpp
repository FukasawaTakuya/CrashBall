/*****************************************************************//**
 * \file   AttackGaugeController.cpp
 * \brief  攻撃ゲージ操作コンポーネント
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#include "pch.h"
#include "AttackGaugeController.h"
#include "Game/Color/GameColor.h"
#include "Game/Engine/Time.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 * \param gameObejct コンポーネントを所有するゲームオブジェクト
 * \param pAttackGauge 攻撃ゲージのポインタ
 * \param pAttackGaugeTrack 攻撃ゲージの土台のポインタ
 * \param pAttackCostText 攻撃コスト表示テキストのポインタ
 */
AttackGaugeController::AttackGaugeController(
	IGameObject* gameObejct, 
	IGameObject* pAttackGauge, 
	IGameObject* pAttackGaugeTrack,
	IGameObject* pAttackPowerText)
	: Component(gameObejct)
	, m_pAttackGauge(pAttackGauge)
	, m_pAttackGaugeTrack(pAttackGaugeTrack)
	, m_pAttackPowerText(pAttackPowerText)
{
	// キャッシュの取得
	m_gaugeRenderer = m_pAttackGauge->GetComponent<SpriteRenderer>();
	m_attackPowerTextRenderer = m_pAttackPowerText->GetComponent<TextRenderer>();
}

/**
 * \brief デストラクタ
 * 
 */
AttackGaugeController::~AttackGaugeController()
{
}

/**
 * \brief 初期化
 * 
 */
void AttackGaugeController::Initilize()
{
	m_gaugeRenderer->SetFillAmount(0.0f);
}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void AttackGaugeController::Update()
{
	// 切り取り量を求める
	float fillValue = 
		static_cast<float>(m_playerMeshCount) / static_cast<float>(m_playerAttackCost);

	// ゲージをスライドさせる
	fillValue = std::lerp(m_gaugeRenderer->GetFillAmount(), fillValue, Time::GetElapsedTime() * GAUGE_SLIDE_SPEED);

	// 1以下に収める
	fillValue = std::min(fillValue, 1.0f);

	// 切り取り量を設定
	m_gaugeRenderer->SetFillAmount(fillValue);

	// テキストを設定
	m_attackPowerTextRenderer->SetText(L"Power:{}", m_playerAttackPower);

	// 攻撃可能かどうかに応じて色を変える
	if (m_playerMeshCount < m_playerAttackCost)
	{
		m_attackPowerTextRenderer->SetColor(GameColor::ATTACKGAUGE_TRACK);
	}
	else
	{
		m_attackPowerTextRenderer->SetColor(GameColor::ATTACKGAUGE);
	}
}
