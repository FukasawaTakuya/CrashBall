/*****************************************************************//**
 * \file   ResourceContext.h
 * \brief  リソース用のコンテキスト
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once

#include "Game/ResourceManager/Interface/IModelManager.h"
#include "Game/ResourceManager/Interface/ISpriteManager.h"
#include "Game/ResourceManager/Interface/ITextManager.h"

/**
 * \brief リソース用のコンテキスト
 */
struct  ResourceContext {

	IModelManager* modelManager;	// モデル管理クラス
	ISpriteManager* spriteManager;	// スプライト管理クラス
	ITextManager* textManager;		// テキスト管理クラス
};
