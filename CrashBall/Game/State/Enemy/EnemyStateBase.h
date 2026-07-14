/*****************************************************************//**
 * \file   EnemyStateBase.h
 * \brief  基底敵ステート
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once

#include "Game/State/StateBase.h"
#include "Game/Component/Enemy/EnemyController.h"
#include "EnemyStateContext.h"

/**
 * \brief 基底敵ステート
 */
class  EnemyStateBase : public StateBase<EnemyController>{

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
protected:

	EnemyStateContext m_stateContext;	// 敵ステート用のコンテキスト

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	EnemyStateBase(const EnemyStateContext& stateContext)
		: m_stateContext(stateContext)
	{}

	// デストラクタ
	~EnemyStateBase() = default;

	// 操作
public:

	// 取得/設定
public:

	// 内部実装
private:

};
