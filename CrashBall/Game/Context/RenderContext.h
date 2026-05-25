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

/**
 * @brief 描画用のコンテキスト
 */
class  RenderContext {

	// データメンバの宣言 -----------------------------------------------
public:

	IModelRendererManager*		m_pModelRendererManager;		// モデル描画管理
	IPrimitiveRendererManager*	m_pPrimitiveRendererManager;	// プリミティブ描画管理
	ISpriteRendererManager*		m_pSpriteRendererManager;		// スプライト描画管理
 
	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	/**
	 * \brief コンストラクタ
	 * 
	 * \param pModelRendererManager モデル描画管理
	 * \param pPrimitiveRendererManager プリミティブ描画管理
	 * \param pSpriteRendererManager スプライト描画管理
	 */
	RenderContext(
		IModelRendererManager*		pModelRendererManager,
		IPrimitiveRendererManager*	pPrimitiveRendererManager,
		ISpriteRendererManager*		pSpriteRendererManager)	
		: m_pModelRendererManager(pModelRendererManager)
		, m_pPrimitiveRendererManager(pPrimitiveRendererManager)
		, m_pSpriteRendererManager(pSpriteRendererManager)
	{}

	// デストラクタ
	~RenderContext() = default;

	// 操作
public:

	// 取得/設定
public:

	// 内部実装
private:

};
