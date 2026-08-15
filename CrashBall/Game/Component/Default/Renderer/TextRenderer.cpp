#include "pch.h"
#include "TextRenderer.h"

using namespace DirectX;

RegisterComponent(TextRenderer)


/**
 * \brief コンストラクタ
 * 
 * \param gameObject コンポーネントを取得するゲームオブジェクト
 */
TextRenderer::TextRenderer(IGameObject* gameObject)
	: Component(gameObject)
{
}

/**
 * \brief デストラクタ
 * 
 */
TextRenderer::~TextRenderer()
{
}

/**
 * \brief アタッチ時の処理
 * 
 */
void TextRenderer::Awake()
{
	m_rectTransform = GetGameObject()->GetComponent<RectTransform>();
}

/**
 * \brief 描画
 * 
 * \param renderContext 描画用のコンテキスト
 */
void TextRenderer::Render(const RenderContext& renderContext)
{
	// 描画命令の登録
	renderContext.textRendererManager->RegisterRenderCommand(
		m_pSpriteFont,
		m_rectTransform->GetWorldPosition(),
		m_color,
		m_rectTransform->GetWorldRotate(),
		m_fontScale * m_rectTransform->GetWorldScale(),
		m_rectTransform->GetOrigin(m_width, m_height),
		m_layerDepth,
		m_text
	);
}
