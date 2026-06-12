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
	SimpleMath::Vector4 offset = FillOriginOffeset[static_cast<int>(m_fillOrigin)] * m_fillAmount;

	SimpleMath::Vector4 baseRect = SourceBaseRECT[static_cast<int>(m_fillOrigin)];

	baseRect.x *= m_width;
	baseRect.z *= m_width;
	baseRect.y *= m_height;
	baseRect.w *= m_height;

	offset.x *= m_width;
	offset.z *= m_width;
	offset.y *= m_height;
	offset.w *= m_height;

	SimpleMath::Vector4 rect = baseRect + offset;

	RECT srcRect = RECT(rect.x, rect.y, rect.z, rect.w);

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
