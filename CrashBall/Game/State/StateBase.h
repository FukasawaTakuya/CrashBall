/*****************************************************************//**
 * \file   StateBase.h
 * \brief  基底ステート 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "IStateMachine.h"
#include "Game/Context/GameContext.h"

/**
 * \brief 基底ステート
 */
template <typename Owner>
class  StateBase {

	// データメンバの宣言 -----------------------------------------------
protected:

	Owner* m_owner = nullptr;					// オーナー

	IStateMachine* m_pStateMachine = nullptr;	// ステートマシンのポインタ

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	StateBase() = default;

	// デストラクタ
	virtual ~StateBase() = default;

	// 操作
public:

	// 開始処理
	virtual void OnEnter() = 0;

	// 更新処理
	virtual void Update(const GameContext& gameContext) = 0;

	// 終了処理
	virtual void OnExit() = 0;	

	// 取得/設定
public:

	// オーナーのセット
	void SetOwner(Owner* owner) { m_owner = owner; }

	// ステートマシンのセット
	void SetStateMachine(IStateMachine* pStateMachine) { m_pStateMachine = pStateMachine; }

	// 内部実装
private:

};
