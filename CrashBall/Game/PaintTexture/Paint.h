#pragma once

#include "Game/ServiceLocator/ServiceLocator.h"
#include "Game/ServiceLocator/IPaintTexture.h"

namespace Paint
{
	// 色を塗る
	inline void Paint(
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Color& color,
		int id)
	{
		IPaintTexture* paintTexture = ServiceLocator::Get<IPaintTexture>();
		if (paintTexture != nullptr)
		{
			paintTexture->RegisterRenderCommnad(position, color, id);
		}
	}

	// ペイントのクリア
	inline void ClearPaint()
	{
		IPaintTexture* paintTexture = ServiceLocator::Get<IPaintTexture>();
		if (paintTexture != nullptr)
		{
			paintTexture->ClearPaint();
		}
	}

	// ペイントテクスチャの取得
	inline ID3D11ShaderResourceView* GetPaintTexture()
	{
		IPaintTexture* paintTexture = ServiceLocator::Get<IPaintTexture>();
		if (paintTexture != nullptr)
		{
			return paintTexture->GetPaintTexture();
		}
		else return nullptr;
	}

	// ペイント時間テクスチャのの取得
	inline ID3D11ShaderResourceView* GetPaintTimeTex()
	{
		IPaintTexture* paintTexture = ServiceLocator::Get<IPaintTexture>();
		if (paintTexture != nullptr)
		{
			return paintTexture->GetPaintTimeTex();
		}
		else return nullptr;
	}

	// レンダーターゲットの取得
	inline ID3D11Texture2D* GetPaintRenderTarget()
	{
		IPaintTexture* paintTexture = ServiceLocator::Get<IPaintTexture>();
		if (paintTexture != nullptr)
		{
			return paintTexture->GetRenderTarget();
		}
		else return nullptr;

	}

	// ペイント時間テクスチャのレンダーターゲットの取得
	inline ID3D11Texture2D* GetPaintTimeRenderTarget()
	{
		IPaintTexture* paintTexture = ServiceLocator::Get<IPaintTexture>();
		if (paintTexture != nullptr)
		{
			return paintTexture->GetPaintTimeRenderTarget();
		}
		else return nullptr;

	}
}
