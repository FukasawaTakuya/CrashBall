/*****************************************************************//**
 * \file   SpriteRenderer.cpp
 * \brief  スプライト描画コンポーネント
 *
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

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
 * \param rendererManager スプライト描画管理クラス
 */
void SpriteRenderer::Render(ISpriteRendererManager* rendererManager)
{
	// オフセット
	SimpleMath::Vector4 offset = FillOriginOffeset[static_cast<int>(m_fillOrigin)];

	// もとの描画領域
	SimpleMath::Vector4 baseRect = SourceBaseRECT[static_cast<int>(m_fillOrigin)];

	SimpleMath::Vector4 Size(m_width, m_height, m_width, m_height);

	// サイズを掛けて実際のオフセット、描画領域に直す
	offset *= Size;
	baseRect *= Size;

	// 描画領域
	SimpleMath::Vector4 rect = baseRect + offset * m_fillAmount;

	// RECTに直す
	RECT srcRect = RECT(rect.x, rect.y, rect.z, rect.w);

	// 描画位置
	SimpleMath::Vector2 position = m_rectTransform->GetPosition();

	// 描画位置をオフセット分ずらす
	position.x -= offset.x * (1.0f - m_fillAmount) * m_spriteScale.x * m_rectTransform->GetScale();
	position.y -= offset.y * (1.0f - m_fillAmount) * m_spriteScale.y * m_rectTransform->GetScale();

	// 描画命令の登録
	rendererManager->RegisterRenderCommand(
		m_pSprite,
		position,
		srcRect,
		m_color,
		m_rectTransform->GetRotate(),
		m_spriteScale * m_rectTransform->GetScale(),
		m_rectTransform->GetOrigin(m_width, m_height),
		m_spriteEffects,
		m_layerDepth
	);
}
