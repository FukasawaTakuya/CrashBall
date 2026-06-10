#include "pch.h"
#include "FloorMeshGaugeController.h"
#include "Game/Common/Screen.h"
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

	m_spriteRenderer->SetColor({ 0.0f, 0.0f, 0.0f, 0.5f });

	m_spriteRenderer->SetLayerDepth(1.0f);

	m_rectTransfrom->SetPosition(SimpleMath::Vector2(Screen::CENTER_X, 50.0f));
	//m_rectTransfrom->SetRotate(XM_PI / 4);
	m_rectTransfrom->SetScale(1.0f);
	m_rectTransfrom->SetOrigin(Origin::Center);

	m_spriteRenderer->SetSpriteScale(SimpleMath::Vector2(8.0f, 0.4f));
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
}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void FloorMeshGaugeController::Update(const GameContext& gameContext)
{
	m_gauge = std::lerp(m_gauge, 0.1f, Time::GetElapsedTime() * 4.0f);

	m_spriteRenderer->SetVelueX(m_gauge);
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

	m_textRenderer->SetText(L"test");
	m_textRenderer->Render(renderer);
}

/**
 * \brief 終了処理
 * 
 */
void FloorMeshGaugeController::Finalize()
{
}
