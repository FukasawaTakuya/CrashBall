#include "pch.h"
#include "TextRenderer.h"

using namespace DirectX;

namespace
{
	const SimpleMath::Vector2 anchorOffeset[static_cast<int>(TextAnchor::AnchorNum)]
	{
		SimpleMath::Vector2(-0.5f, -0.5f),	// Center
		SimpleMath::Vector2(0.0f,  0.0f),	// LeftTop
		SimpleMath::Vector2(0.0f, -0.5f),	// LeftCenter
		SimpleMath::Vector2(-1.0f,  0.0f),	// RightTop
		SimpleMath::Vector2(-1.0f, -0.5f),	// RightCenter
	};
}


/**
 * \brief コンストラクタ
 * 
 * \param コンポーネントを取得するゲームオブジェクト
 */
TextRenderer::TextRenderer(IGameObject* gameObject)
	: Component(gameObject)
{
	m_rectTransform = GetGameObject()->GetComponent<RectTransform>();
}

/**
 * \brief デストラクタ
 * 
 */
TextRenderer::~TextRenderer()
{
}

/**
 * \brief 描画
 * 
 * \param renderContext 描画用のコンテキスト
 */
void TextRenderer::Render(RenderContext& renderContext)
{
	ITextRendererManager* rendererManager = renderContext.textRendererManager;

	SimpleMath::Vector2 offset = anchorOffeset[static_cast<int>(m_anchor)];

	SimpleMath::Vector2 position =
		m_rectTransform->GetPosition() + SimpleMath::Vector2(m_width, m_height) * offset;

	rendererManager->RegisterRenderCommand(
		position,
		m_color,
		m_rectTransform->GetScale(),
		SimpleMath::Vector2::Zero,
		m_layerDepth,
		m_text
	);
}
