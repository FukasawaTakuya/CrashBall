#include "pch.h"
#include "PaintMeshBar.h"

#include "Game/Component/Default/RectTransform.h"
#include "Game/Component/Default/SpriteRenderer.h"

/**
 * \brief コンストラクタ
 * 
 */
PaintMeshBar::PaintMeshBar()
{
	AddComponent<RectTransform>();
	m_spriteRenderer = AddComponent<SpriteRenderer>();
	m_spriteRenderer->SetLayerDepth(LAYER_DEPTH);
}

/**
 * \brief デストラクタ
 * 
 */
PaintMeshBar::~PaintMeshBar()
{
}

/**
 * \brief 初期化
 * 
 */
void PaintMeshBar::Initialize()
{
}

/**
 * \brief 更新
 * 
 * \param gameContext
 */
void PaintMeshBar::Update(const GameContext& gameContext)
{
}

/**
 * \brief 描画
 * 
 * \param renderContext
 */
void PaintMeshBar::Render(const RenderContext& renderContext)
{
	ISpriteRendererManager* rendererManager = renderContext.spriteRendererManager;
	m_spriteRenderer->Render(rendererManager);
}

/**
 * \brief 終了処理
 * 
 */
void PaintMeshBar::Finalize()
{
}
