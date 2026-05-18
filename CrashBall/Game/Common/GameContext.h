#pragma once

#include "Game/Interface/IInputSystem.h"
#include "Game/Interface/ITimeManager.h"
#include "Game/Interface/IModelManager.h"
#include "Game/Interface/IModelRendererManager.h"
#include "Game/Interface/IPrimitiveRendererManager.h"

/**
 * @brief 基底オブジェクト
 */
class  GameContext {

	// データメンバの宣言 -----------------------------------------------
public:

	ITimeManager*				m_pTimeManager;
	IModelManager*				m_pModelManager;
	IModelRendererManager*		m_pModelRendererManager;
	IPrimitiveRendererManager*	m_pPrimitiveRendererManager;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	GameContext(
		ITimeManager*				pTimeManager,
		IModelManager*				pModelManager,
		IModelRendererManager*		pModelRendererManager,
		IPrimitiveRendererManager*	pPrimitiveRendererManager
	)	: m_pTimeManager(pTimeManager)
		, m_pModelManager(pModelManager)
		, m_pModelRendererManager(pModelRendererManager)
		, m_pPrimitiveRendererManager(pPrimitiveRendererManager)
	{}

	// デストラクタ
	~GameContext() = default;

	// 操作
public:

	// 取得/設定
public:

	// 内部実装
private:

};
