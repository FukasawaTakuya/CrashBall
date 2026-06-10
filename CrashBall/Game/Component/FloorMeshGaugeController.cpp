#include "pch.h"
#include "FloorMeshGaugeController.h"

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

	m_rectTransfrom->SetPosition(SimpleMath::Vector2(640, 360));
	//m_rectTransfrom->SetRotate(XM_PI / 4);
	m_rectTransfrom->SetOrigin(Origin::Center);
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
