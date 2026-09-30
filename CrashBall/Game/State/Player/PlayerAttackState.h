/*****************************************************************//**
 * \file   PlayerAttackState.h
 * \brief  プレイヤー攻撃ステート 
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once

#include "PlayerStateBase.h"

#include "Game/Common/Easing.h"

/**
 * \brief プレイヤー攻撃ステート
 */
class  PlayerAttackState : public PlayerStateBase
{

	// データメンバの宣言 -----------------------------------------------
private:

	float m_timer;		// タイマー

	Easing<float> m_hitStopTimer;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	PlayerAttackState(const PlayerStateContext& stateContext);

	// デストラクタ
	~PlayerAttackState();

	// 操作
private:

	// 開始処理
	void OnEnter() override;

	// 更新処理
	void Update(const GameContext& gameContext) override;

	// 終了処理
	void OnExit() override;

	// 内部実装
private:

};
