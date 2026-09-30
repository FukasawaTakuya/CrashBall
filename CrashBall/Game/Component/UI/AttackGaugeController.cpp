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
 * \brief アタッチ時の処理
 * 
 */
void AttackGaugeController::Awake()
{
	// コンポーネントのキャッシュの取得
	m_attackPowerTextRenderer = m_pAttackPowerText->GetComponent<TextRenderer>();
	m_attackGaugeController = m_pAttackGauge->GetComponent<SliderController>();

	m_gameColor = Scriptable::GetScriptableObject<GameColor>();
}

/**
 * \brief 開始処理
 * 
 * \param gameContext ゲーム用のコンテキスト
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
	int playerMeshCount = m_pStageController->GetPlayerMeshCount();			// プレイヤーの面の数
	int playerAttackCost = m_pPlayerStatusController->GetAttacckCost();		// プレイヤーの攻撃コスト
	int playerAttackPower = m_pPlayerStatusController->GetAttackPower();	// プレイヤーの攻撃力

	// 切り取り量を求める
	float fillValue = 
		static_cast<float>(playerMeshCount) / static_cast<float>(playerAttackCost);

	// 目標値の設定
	m_attackGaugeController->SetTargetAmount(fillValue);
	// スライド
	m_attackGaugeController->Slide();

	// テキストを設定
	m_attackPowerTextRenderer->SetText(L"Power:{}", playerAttackPower);

	// 攻撃可能かどうかに応じて色を変える
	if (playerMeshCount >= playerAttackCost)
	{
		m_attackPowerTextRenderer->SetColor(m_gameColor->m_attackGaugeColor);
	}
	else
	{
		m_attackPowerTextRenderer->SetColor(m_gameColor->m_attackGaugeTrackColor);
	}
}
