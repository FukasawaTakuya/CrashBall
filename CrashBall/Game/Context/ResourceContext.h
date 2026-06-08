/*****************************************************************//**
 * \file   ResourceContext.h
 * \brief  リソース用のコンテキスト
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once

#include "Game/Interface/IModelManager.h"

#include "Game/Interface/ISpriteManager.h"

/**
 * \brief リソース用のコンテキスト
 */
struct  ResourceContext {

	IModelManager* modelManager;	// モデル管理クラス
	ISpriteManager* spriteManager;	// スプライト管理クラス

};
