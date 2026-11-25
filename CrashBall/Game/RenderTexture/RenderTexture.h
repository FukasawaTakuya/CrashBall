/*****************************************************************//**
 * \file   RenderTexture.h
 * \brief  レンダーテクスチャ管理関数をまとめたヘッダーファイル
 * 
 * \author 深沢拓矢
 * \date   October 2026
 *********************************************************************/

#pragma once

#include "Game/ServiceLocator/IRenderTargetManager.h"
#include "Game/ServiceLocator/ServiceLocator.h"

namespace RenderTexture
{
	// レンダーテクスチャの作成
	inline MyRenderTexture* CreateRenderTexture(bool isDepth = false)
	{
		IRenderTargetManager* renderTargetManager = ServiceLocator::Get<IRenderTargetManager>();

		if (renderTargetManager != nullptr)
		{
			return renderTargetManager->CreateRenderTexture(isDepth);
		}
		else
		{
			return nullptr;
		}
	}

	// レンダーテクスチャの削除
	inline void DeleteRenderTexture(MyRenderTexture* renderTexture)
	{
		IRenderTargetManager* renderTargetManager = ServiceLocator::Get<IRenderTargetManager>();

		if (renderTargetManager != nullptr)
		{
			renderTargetManager->DeleteRenderTexture(renderTexture);
		}
	}
}
