/*****************************************************************//**
 * \file   AttackGaugeController.cpp
 * \brief  攻撃ゲージ操作コンポーネント
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#include "pch.h"
#include "AttackGaugeController.h"
#include "PlayerStatusController.h"
#include "Game/Color/GameColor.h"
#include "Game/Engine/Time.h"
#include "Default/TextRenderer.h"


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
	IGameObject* pAttackGaugeTrack
	)
	: Component(gameObejct)
	, m_pAttackGauge(pAttackGauge)
	, m_pAttackGaugeTrack(pAttackGaugeTrack)
{
	// 描画位置の設定
	m_pAttackGauge->GetComponent<RectTransform>()
		->SetPosition(GAUGE_POSITION);
	m_pAttackGaugeTrack->GetComponent<RectTransform>()
		->SetPosition(GAUGE_POSITION);

	// キャッシュの取得
	m_gaugeRenderer = m_pAttackGauge->GetComponent<SpriteRenderer>();

	SpriteRenderer* gaugeTrackRenderer = m_pAttackGaugeTrack->GetComponent<SpriteRenderer>();

	// 描画順の設定
	m_gaugeRenderer->SetLayerDepth(0.1f);

	// スプライトのスケールの設定
	m_gaugeRenderer->SetSpriteScale(0.4f);
	gaugeTrackRenderer->SetSpriteScale(0.4f);

	// 色の設定
	m_gaugeRenderer->SetColor(GameColor::ATTACKGAUGE);
	gaugeTrackRenderer->SetColor(GameColor::ATTACKGAUGE_TRACK);

	// 切り取り原点の設定
	m_gaugeRenderer->SetFillOrigin(FillOrigin::Top);
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
void AttackGaugeController::Update(const GameContext& gameContext)
{
	// 切り取り量を求める
	float fillValue = 
		static_cast<float>(m_playerMeshCount) / static_cast<float>(m_playerAttackCost);

	// ゲージをスライドさせる
	fillValue = std::lerp(m_gaugeRenderer->GetFillAmount(), fillValue, Time::GetElapsedTime() * 5.0f);

	// 1以下に収める
	fillValue = std::min(fillValue, 1.0f);

	m_gaugeRenderer->SetFillAmount(fillValue);

}
