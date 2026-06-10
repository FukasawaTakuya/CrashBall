#include "pch.h"
#include "SpriteRenderer.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 * \param gameObject コンポーネントを所有しているオブジェクト
 */
SpriteRenderer::SpriteRenderer(IGameObject* gameObject)
	: Component(gameObject)
{
	m_rectTransform = GetGameObject()->GetComponent<RectTransform>();
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
 * \param rendererManager 描画管理クラス
 */
void SpriteRenderer::Render(ISpriteRendererManager* rendererManager)
{
	// 切り取り領域
	RECT srcRect = RECT(0.0f, 0.0f, m_width * m_valueX, m_height * m_valueY);

	// 描画命令の登録
	rendererManager->RegisterRenderCommand(
		m_pSprite,
		m_rectTransform->GetPosition(),
		srcRect,
		m_color,
		m_rectTransform->GetRotate(),
		m_spriteScale * m_rectTransform->GetScale(),
		m_rectTransform->GetOrigin(m_width, m_height),
		m_layerDepth
	);
}
