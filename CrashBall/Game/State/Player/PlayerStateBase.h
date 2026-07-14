/*****************************************************************//**
 * \file   PlayerStateBase.h
 * \brief  基底プレイヤーステート
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once

#include "Game/State/StateBase.h"
#include "Game/Component/Player/PlayerController.h"
#include "PlayerStateContext.h"

/**
 * \brief 基底プレイヤーステート
 */
class  PlayerStateBase : public StateBase<PlayerController>{

	// データメンバの宣言 -----------------------------------------------
protected:

	PlayerStateContext m_stateContext;	// プレイヤーステート用のコンテキスト

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// デフォルトコンストラクタ
	PlayerStateBase() = default;

	// コンストラクタ
	PlayerStateBase(const PlayerStateContext& stateContext)
		: m_stateContext(stateContext)
	{}

	// デストラクタ
	~PlayerStateBase() = default;

	// 操作
public:

	// 取得/設定
public:

	// 内部実装
private:

};
