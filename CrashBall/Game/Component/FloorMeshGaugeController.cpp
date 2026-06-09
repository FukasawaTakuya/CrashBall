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

	m_spriteRenderer->SetColor({ 0.0f, 0.0f, 0.0f, 0.5f });

	m_spriteRenderer->SetLayerDepth(1.0f);
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

	m_spriteRenderer->Render(rendererManger);
}

/**
 * \brief 終了処理
 * 
 */
void FloorMeshGaugeController::Finalize()
{
}
