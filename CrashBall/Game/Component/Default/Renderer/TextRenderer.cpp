#include "pch.h"
#include "TextRenderer.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 * \param gameObject コンポーネントを取得するゲームオブジェクト
 */
TextRenderer::TextRenderer(IGameObject* gameObject)
	: Component(gameObject)
{
	m_rectTransform = GetGameObject()->GetComponent<RectTransform>();
}

/**
 * \brief コピーコンストラクタ
 * 
 * \param gameObject コンポーネントを取得するゲームオブジェクト
 * \param textRenderer テキスト描画コンポーネント
 */
TextRenderer::TextRenderer(
	IGameObject* gameObject, 
	const TextRenderer& textRenderer)
	: Component(gameObject)
	, m_text(textRenderer.m_text)
	, m_color(textRenderer.m_color)
	, m_fontScale(textRenderer.m_fontScale)
	, m_layerDepth(textRenderer.m_layerDepth)
{
	// テキストのサイズを求める
	CalcTextSize();
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
