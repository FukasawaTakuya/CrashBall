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
class  ResourceContext {

	// クラス定数の宣言 -------------------------------------------------
public:

	IModelManager* m_pModelManager;
	ISpriteManager* m_pSpriteManager;

	// データメンバの宣言 -----------------------------------------------
private:

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	/**
	 * \brief コンストラクタ
	 * 
	 * \param pModelManager モデル管理
	 * \param pSpriteManager スプライト管理
	 */
	ResourceContext(
		IModelManager*	pModelManager,
		ISpriteManager* pSpriteManager)
		: m_pModelManager	(pModelManager)
		, m_pSpriteManager	(pSpriteManager)
	{}

	// デストラクタ
	~ResourceContext() = default;

	// 操作
public:

	// 取得/設定
public:

	// 内部実装
private:

};
