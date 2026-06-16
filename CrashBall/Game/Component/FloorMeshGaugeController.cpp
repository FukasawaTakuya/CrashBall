#include "pch.h"
#include "FloorMeshGaugeController.h"
#include "Game/Engine/Time.h"

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
	// コンポーネントのキャッシュ
	m_gaugeTrackRenderer = m_pGaugeTrack->GetComponent<SpriteRenderer>();
	m_gaugeTrackTransform = m_pGaugeTrack->GetComponent<RectTransform>();
	// 描画位置
	m_gaugeTrackTransform->SetPosition(POSITION);
	// 基準位置
	m_gaugeTrackTransform->SetOrigin(Origin::Center);
	// 
	m_gaugeTrackRenderer->SetLayerDepth(0.1f);

	// 背景の描画コンポーネント
	SpriteRenderer* backGroundRenderer
		= m_pGaugeBackGround->GetComponent<SpriteRenderer>();
	// スケール
	backGroundRenderer->SetSpriteScale(SimpleMath::Vector2(1.1f, 3.0f));
	// 色
	backGroundRenderer->SetColor({ 0.0f, 0.0f, 0.0f, 0.4f });
	// 背景の初期位置設定
	m_pGaugeBackGround->GetComponent<RectTransform>()->SetPosition({ Screen::CENTER_X, Screen::HEIGHT - 50.f });

	// ゲージのコンポーネントのキャッシュの取得
	m_playerGaugeRenderer = m_pPalyerMeshGauge->GetComponent<SpriteRenderer>();
	m_playerGaugeTransform = m_pPalyerMeshGauge->GetComponent<RectTransform>();
	m_enemyGaugeRenderer = m_pEnemyMeshGauge->GetComponent<SpriteRenderer>();
	m_enemyGaugeTransform = m_pEnemyMeshGauge->GetComponent<RectTransform>();

	// 描画順の設定
	m_playerGaugeRenderer->SetLayerDepth(GAUGE_LAYER_DEPTH);
	m_enemyGaugeRenderer->SetLayerDepth(GAUGE_LAYER_DEPTH);

	// 基準位置の設定
	m_playerGaugeTransform->SetOrigin(Origin::LeftCenter);
	m_enemyGaugeTransform->SetOrigin(Origin::LeftCenter);

	// 切り取りの起点の設定
	m_enemyGaugeRenderer->SetFillOrigin(FillOrigin::Right);

	RectTransform* playerTextTransform = m_pPlayerMeshNumText->GetComponent<RectTransform>();
	RectTransform* enemyTextTransform = m_pEnemyMeshNumText->GetComponent<RectTransform>();
	// テキストの初期位置
	playerTextTransform->SetPosition({ Screen::CENTER_X - 250.0f, Screen::HEIGHT - 85.0f });
	enemyTextTransform->SetPosition({ Screen::CENTER_X + 250.0f, Screen::HEIGHT - 85.0f });

	// 
	m_playerTextRenderer = pPlayerMeshNumText->GetComponent<TextRenderer>();
	m_enemyTextRenderer = pEnemyMeshNumText->GetComponent<TextRenderer>();
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
	// 色の設定
	m_playerGaugeRenderer->SetColor(m_floorMeshGetter->GetPlayerColor());
	m_enemyGaugeRenderer->SetColor(m_floorMeshGetter->GetEnemyColor());

	// テキストの色の設定
	m_playerTextRenderer->SetColor(m_floorMeshGetter->GetPlayerColor());
	m_enemyTextRenderer->SetColor(m_floorMeshGetter->GetEnemyColor());


	// 切り取り量の設定
	m_playerGaugeRenderer->SetFillAmount(0.0f);
	m_enemyGaugeRenderer->SetFillAmount(0.0f);

	m_enemyGaugeTransform
		->SetPosition({ m_playerGaugeTransform->GetRight(m_playerGaugeRenderer->GetWidth()), POSITION.y });
	// 描画位置の設定
	m_playerGaugeTransform
		->SetPosition({ m_gaugeTrackTransform->GetLeft(m_gaugeTrackRenderer->GetWidth()), POSITION.y });
}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void FloorMeshGaugeController::Update(const GameContext& gameContext)
{
	// 全体の面に対する塗った面の割合
	float playerFillAmount = (float)m_floorMeshGetter->GetPlayerMeshCount() / (float)m_floorMeshGetter->GetTotalMeshCount();
	float enemyFillAmount = (float)m_floorMeshGetter->GetEnemyMeshCount() / (float)m_floorMeshGetter->GetTotalMeshCount();

	// 線形補完でスライドさせる
	playerFillAmount = std::lerp(m_playerGaugeRenderer->GetFillAmount(), playerFillAmount, Time::GetElapsedTime() * 5.0f);
	enemyFillAmount = std::lerp(m_enemyGaugeRenderer->GetFillAmount(), enemyFillAmount, Time::GetElapsedTime() * 5.0f);

	// 切り取り量の設定
	m_playerGaugeRenderer->SetFillAmount(playerFillAmount);
	m_enemyGaugeRenderer->SetFillAmount(enemyFillAmount);

	// 敵のバーの位置を設定
	m_enemyGaugeTransform
		->SetPosition({ m_playerGaugeTransform->GetRight(m_playerGaugeRenderer->GetWidth()), POSITION.y });

	m_playerTextRenderer->SetText(L"Player:{}面", m_floorMeshGetter->GetPlayerMeshCount());
	m_enemyTextRenderer->SetText(L"Enemy:{}面", m_floorMeshGetter->GetEnemyMeshCount());

	m_playerTextRenderer->SetFontScale(0.75f);
	m_enemyTextRenderer->SetFontScale(0.75f);
}

/**
 * \brief 描画処理
 * 
 * \param renderContext 描画用のコンテキスト
 */
void FloorMeshGaugeController::Render(const RenderContext& renderContext)
{
	ISpriteRendererManager* sprite = renderContext.spriteRendererManager;
	ITextRendererManager* text = renderContext.textRendererManager;

	//m_spriteRenderer->Render(sprite);
}

/**
 * \brief 終了処理
 * 
 */
void FloorMeshGaugeController::Finalize()
{
}
