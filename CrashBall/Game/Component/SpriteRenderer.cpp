#include "pch.h"
#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer()
{
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::SetSprite(ID3D11ShaderResourceView* pSprite)
{
	m_pSprite = pSprite;
}
