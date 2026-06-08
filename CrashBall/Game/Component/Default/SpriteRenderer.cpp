#include "pch.h"
#include "SpriteRenderer.h"

/**
 * \brief コンストラクタ
 * 
 * \param gameObject コンポーネントを所有しているオブジェクト
 */
SpriteRenderer::SpriteRenderer(IGameObject* gameObject)
	: Component(gameObject)
{
}

/**
 * \brief デストラクタ
 * 
 */
SpriteRenderer::~SpriteRenderer()
{
}

/**
 * \brief 描画
 * 
 * \param rendererManager 描画管理
 * \param rect 描画範囲
 */
void SpriteRenderer::Render(ISpriteRendererManager* rendererManager, const RECT& rect)
{
	rendererManager->RegisterRenderCommand(
		m_pSprite,
		rect,
		m_orderInLayer,
		m_color
	);
}
