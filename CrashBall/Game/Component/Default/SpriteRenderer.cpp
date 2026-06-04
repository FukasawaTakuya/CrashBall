#include "pch.h"
#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(IGameObject* owner)
	: Component(owner)
{
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::Render(ISpriteRendererManager* rendererManager, const RECT& rect)
{
	//rendererManager
}

void SpriteRenderer::SetSprite(ID3D11ShaderResourceView* pSprite)
{
	m_pSprite = pSprite;
}
