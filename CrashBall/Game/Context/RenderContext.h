/*****************************************************************//**
 * \file   RenderContext.h
 * \brief  描画用のコンテキスト
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once

#include "Game/Interface/IModelRendererManager.h"
#include "Game/Interface/IPrimitiveRendererManager.h"
#include "Game/Interface/ISpriteRendererManager.h"
#include "Game/Interface/ITextRendererManager.h"

/**
 * @brief 描画用のコンテキスト
 */
struct  RenderContext {

	IModelRendererManager*		modelRendererManager;		// モデル描画管理
	IPrimitiveRendererManager*	primitiveRendererManager;	// プリミティブ描画管理
	ISpriteRendererManager*		spriteRendererManager;		// スプライト描画管理
	ITextRendererManager*		textRendererManager;		// テキスト描画管理

};
