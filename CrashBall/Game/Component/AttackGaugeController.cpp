#include "pch.h"
#include "AttackGaugeController.h"
#include "Game/Common/Screen.h"
#include "PlayerStatusController.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 * \param gameObejct コンポーネントを所有するゲームオブジェクト
 * \param pAttackGauge 攻撃ゲージのポインタ
 * \param pAttackGaugeTrack 攻撃ゲージの土台のポインタ
 */
AttackGaugeController::AttackGaugeController(
	IGameObject* gameObejct, 
	IGameObject* pAttackGauge, 
	IGameObject* pAttackGaugeTrack)
	: Component(gameObejct)
	, m_pAttackGauge(pAttackGauge)
	, m_pAttackGaugeTrack(pAttackGaugeTrack)
{
	// 描画位置の設定
	m_pAttackGauge->GetComponent<RectTransform>()
		->SetPosition({ Screen::CENTER_X, Screen::CENTER_Y + 150.f });
	m_pAttackGaugeTrack->GetComponent<RectTransform>()
		->SetPosition({ Screen::CENTER_X, Screen::CENTER_Y + 150.f });

	// キャッシュの取得
	m_gaugeRenderer = m_pAttackGauge->GetComponent<SpriteRenderer>();
	m_gaugeTrackRenderer = m_pAttackGaugeTrack->GetComponent<SpriteRenderer>();

	// 描画順の設定
	m_gaugeRenderer->SetLayerDepth(0.1f);

	// スプライトのスケールの設定
	m_gaugeRenderer->SetSpriteScale(0.4f);
	m_gaugeTrackRenderer->SetSpriteScale(0.4f);

	m_gaugeRenderer->SetColor(GAUGE_COLOR);
	m_gaugeTrackRenderer->SetColor(GAUGE_TRACK_COLOR);

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
		static_cast<float>(m_floorMeshGetter->GetPlayerMeshCount()) / static_cast<float>(PlayerStatusController::ATTACK_COST);

	// 1以下に収める
	fillValue = std::min(fillValue, 1.0f);

	m_gaugeRenderer->SetFillAmount(fillValue);

}
