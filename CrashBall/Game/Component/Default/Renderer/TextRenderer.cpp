#include "pch.h"
#include "TextRenderer.h"

using namespace DirectX;

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
void TextRenderer::Render(ITextRendererManager* rendererManager)
{
	// 描画命令の登録
	rendererManager->RegisterRenderCommand(
		m_pSpriteFont,
		m_rectTransform->GetPosition(),
		m_color,
		m_rectTransform->GetRotate(),
		m_fontScale * m_rectTransform->GetScale(),
		m_rectTransform->GetOrigin(m_width, m_height),
		m_layerDepth,
		m_text
	);
}
