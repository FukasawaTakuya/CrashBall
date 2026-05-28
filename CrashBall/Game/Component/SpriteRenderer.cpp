#include "pch.h"
#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(IGameObject* owner)
	: Component(owner)
{
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::SetSprite(ID3D11ShaderResourceView* pSprite)
{
	m_pSprite = pSprite;
}
