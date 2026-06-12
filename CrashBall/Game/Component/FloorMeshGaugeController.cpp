#include "pch.h"
#include "FloorMeshGaugeController.h"
#include "Game/Engine/Time.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 */
FloorMeshGaugeController::FloorMeshGaugeController(IGameObject* gameObject)
	: Component(gameObject)
{
	// コンポーネントのキャッシュ
	m_spriteRenderer = GetGameObject()->GetComponent<SpriteRenderer>();
	m_rectTransfrom = GetGameObject()->GetComponent<RectTransform>();
	m_textRenderer = GetGameObject()->GetComponent<TextRenderer>();

	// 描画位置
	m_rectTransfrom->SetPosition(POSITION);
	// 基準位置
	m_rectTransfrom->SetOrigin(Origin::Center);

	// テキストの色
	m_textRenderer->SetColor(Colors::Black);
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
	// コンポーネントのキャッシュの取得
	m_playerBarSpriteRenderer	= m_pPalyerMeshBar->GetComponent<SpriteRenderer>();
	m_playerBarRectTransform	= m_pPalyerMeshBar->GetComponent<RectTransform>();
	m_enemyBarSpriteRenderer	= m_pEnemyMeshBar->GetComponent<SpriteRenderer>();
	m_enemyBarRectTransform		= m_pEnemyMeshBar->GetComponent<RectTransform>();

	// 色の設定
	m_playerBarSpriteRenderer->SetColor(m_floorMeshGetter->GetPlayerColor());
	m_enemyBarSpriteRenderer->SetColor(m_floorMeshGetter->GetEnemyColor());

	// 基準位置の設定
	m_playerBarRectTransform->SetOrigin(Origin::LeftCenter);
	m_enemyBarRectTransform->SetOrigin(Origin::LeftCenter);

	m_playerBarSpriteRenderer->SetFillAmount(0.0f);
	m_enemyBarSpriteRenderer->SetFillAmount(0.0f);

	m_enemyBarSpriteRenderer->SetFillOrigin(FillOrigin::Right);

	// 描画位置の設定
	m_playerBarRectTransform
		->SetPosition({ m_rectTransfrom->GetLeft(m_spriteRenderer->GetWidth()), POSITION.y });
	m_enemyBarRectTransform
		->SetPosition({ m_playerBarRectTransform->GetRight(m_playerBarSpriteRenderer->GetWidth()), POSITION.y });

	m_textRenderer->SetText(L"test");

}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void FloorMeshGaugeController::Update(const GameContext& gameContext)
{
	float playerValue = (float)m_floorMeshGetter->GetPlayerMeshCount() / (float)m_floorMeshGetter->GetTotalMeshCount();
	float enemyValue = (float)m_floorMeshGetter->GetEnemyMeshCount() / (float)m_floorMeshGetter->GetTotalMeshCount();

	playerValue = std::lerp(m_playerBarSpriteRenderer->GetFillAmount(), playerValue, Time::GetElapsedTime() * 5.0f);
	enemyValue = std::lerp(m_enemyBarSpriteRenderer->GetFillAmount(), enemyValue, Time::GetElapsedTime() * 5.0f);

	m_playerBarSpriteRenderer->SetFillAmount(playerValue);
	m_enemyBarSpriteRenderer->SetFillAmount(enemyValue);

	// 敵のバーの位置を設定
	m_enemyBarRectTransform
		->SetPosition({ m_playerBarRectTransform->GetRight(m_playerBarSpriteRenderer->GetWidth()) - 1.0f, POSITION.y });
}

/**
 * \brief 描画処理
 * 
 * \param renderContext 描画用のコンテキスト
 */
void FloorMeshGaugeController::Render(const RenderContext& renderContext)
{
	ISpriteRendererManager* rendererManger = renderContext.spriteRendererManager;
	ITextRendererManager* renderer = renderContext.textRendererManager;

	m_spriteRenderer->Render(rendererManger);

	m_textRenderer->Render(renderer);
}

/**
 * \brief 終了処理
 * 
 */
void FloorMeshGaugeController::Finalize()
{
}

void FloorMeshGaugeController::SetContext(
	IFloorMeshGetter* floorMeshGetter, 
	IGameObject* pPlayerMeshBar, 
	IGameObject* pEnemyMeshBar)
{
	m_floorMeshGetter = floorMeshGetter;
	m_pPalyerMeshBar = pPlayerMeshBar;
	m_pEnemyMeshBar = pEnemyMeshBar;
}
