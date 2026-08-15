/*****************************************************************//**
 * \file   AttackGaugeController.cpp
 * \brief  攻撃ゲージ操作コンポーネント
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#include "pch.h"
#include "AttackGaugeController.h"
#include "Game/Engine/Time.h"
#include "Game/ScriptableObject/Scriptable.h"

using namespace DirectX;
RegisterComponent(AttackGaugeController)

/**
 * \brief コンストラクタ
 *
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 */
AttackGaugeController::AttackGaugeController(IGameObject* gameObject)
	: Component(gameObject)
{
}


/**
 * \brief デストラクタ
 * 
 */
AttackGaugeController::~AttackGaugeController()
{
}

void AttackGaugeController::Awake()
{
	// コンポーネントのキャッシュの取得
	m_attackPowerTextRenderer = m_pAttackPowerText->GetComponent<TextRenderer>();
	m_attackGaugeController = m_pAttackGauge->GetComponent<SliderController>();

	m_gameColor = Scriptable::GetScriptableObject("gameColor");
}

/**
 * \brief 初期化
 * 
 */
void AttackGaugeController::Start(const GameContext& gameContext)
{
	m_attackGaugeController->SetCurrentAmount(0.0f);
}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void AttackGaugeController::Update(const GameContext& gameContext)
{
	// 切り取り量を求める
	float fillValue = 
		static_cast<float>(m_playerMeshCount) / static_cast<float>(m_playerAttackCost);

	// 目標値の設定
	m_attackGaugeController->SetTargetAmount(fillValue);
	// スライド
	m_attackGaugeController->Slide();

	// テキストを設定
	m_attackPowerTextRenderer->SetText(L"Power:{}", m_playerAttackPower);

	// 攻撃可能かどうかに応じて色を変える
	if (m_playerMeshCount >= m_playerAttackCost)
	{
		m_attackPowerTextRenderer->SetColor(m_gameColor->GetValue<SimpleMath::Color>("AttackGaugeColor"));
	}
	else
	{
		m_attackPowerTextRenderer->SetColor(m_gameColor->GetValue<SimpleMath::Color>("AttackGaugeTrackColor"));
	}
}
