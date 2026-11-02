#pragma once

#include "Game/ServiceLocator/ServiceLocator.h"
#include "Game/ServiceLocator/IPaintTexture.h"

namespace Paint
{
	void Paint(
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Color& color)
	{
		IPaintTexture* paintTexture = ServiceLocator::Get<IPaintTexture>();
		if (paintTexture != nullptr)
		{
			paintTexture->RegisterRenderCommnad(position, color);
		}
	}

	ID3D11ShaderResourceView* GetPaintTexture()
	{
		IPaintTexture* paintTexture = ServiceLocator::Get<IPaintTexture>();
		if (paintTexture != nullptr)
		{
			return paintTexture->GetPaintTexture();
		}
		else return nullptr;
	}
}
