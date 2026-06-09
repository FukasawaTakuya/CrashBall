#include "pch.h"
#include "SpriteRenderer.h"

using namespace DirectX;

namespace
{
	const SimpleMath::Vector2 anchorOffeset[static_cast<int>(Anchor::AnchorNum)]
	{
		SimpleMath::Vector2(-0.5f, -0.5f),	// Center
		SimpleMath::Vector2( 0.0f,  0.0f),	// LeftTop
		SimpleMath::Vector2( 0.0f, -0.5f),	// LeftCenter
		SimpleMath::Vector2(-1.0f,  0.0f),	// RightTop
		SimpleMath::Vector2(-1.0f, -0.5f),	// RightCenter
	};
}

/**
 * \brief コンストラクタ
 * 
 * \param gameObject コンポーネントを所有しているオブジェクト
 */
SpriteRenderer::SpriteRenderer(IGameObject* gameObject, Anchor anchor)
	: Component(gameObject)
	, m_anchor(anchor)
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
 * \param rendererManager 描画管理
 * \param rect 描画範囲
 */
void SpriteRenderer::Render(ISpriteRendererManager* rendererManager)
{
	// アンカーを決めるためのオフセット
	SimpleMath::Vector2 offset = anchorOffeset[static_cast<int>(m_anchor)];

	// 描画領域
	RECT rect =
	{
		m_rectTransform->GetPosition().x + m_width  * m_rectTransform->GetScale() * offset.x,
		m_rectTransform->GetPosition().y + m_height * m_rectTransform->GetScale() * offset.y,
		m_rectTransform->GetPosition().x + m_width  * m_rectTransform->GetScale() * offset.x + m_width  * m_rectTransform->GetScale(),
		m_rectTransform->GetPosition().y + m_height * m_rectTransform->GetScale() * offset.y + m_height * m_rectTransform->GetScale(),
	};

	// 描画命令の登録
	rendererManager->RegisterRenderCommand(
		m_pSprite,
		m_rectTransform->GetPosition(),
		SimpleMath::Vector2::Zero,
		m_layerDepth,
		m_color
	);

}
