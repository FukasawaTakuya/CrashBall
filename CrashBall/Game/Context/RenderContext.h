/*****************************************************************//**
 * \file   RenderContext.h
 * \brief  描画用のコンテキスト
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once

#include "Game/RendererManager/Interface/IModelRendererManager.h"
#include "Game/RendererManager/Interface/IPrimitiveRendererManager.h"
#include "Game/RendererManager/Interface/ISpriteRendererManager.h"
#include "Game/RendererManager/Interface/ITextRendererManager.h"

/**
 * @brief 描画用のコンテキスト
 */
struct  RenderContext {

	IModelRendererManager*		modelRendererManager;		// モデル描画管理
	IPrimitiveRendererManager*	primitiveRendererManager;	// プリミティブ描画管理
	ISpriteRendererManager*		spriteRendererManager;		// スプライト描画管理
	ITextRendererManager*		textRendererManager;		// テキスト描画管理

};
