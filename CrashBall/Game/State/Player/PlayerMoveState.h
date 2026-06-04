/*****************************************************************//**
 * \file   PlayerMoveState.h
 * \brief  プレイヤー移動ステート 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "PlayerStateBase.h"

class Player;

/**
 * \brief プレイヤー移動ステート
 */
class  PlayerMoveState : public PlayerStateBase {

	// クラス定数の宣言 -------------------------------------------------
public:

	static constexpr float ACCELERATION = 35.0f;	// 加速度 

	static constexpr float MAX_SPEED = 40.0f;		// 最大速度

	static constexpr int ATTACK_COST_FACE_COUNT = 20;	// 消費する面の数


	// データメンバの宣言 -----------------------------------------------
private:

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	PlayerMoveState(const PlayerStateContext& stateContext);

	// デストラクタ
	~PlayerMoveState();

	// 操作
private:
	// 初期化処理
	void Initialize() override;

	// 開始処理
	void OnEnter() override;

	// 更新処理
	void Update() override;

	// 終了処理
	void OnExit() override;

	// 取得/設定
public:

	// 内部実装
private:

};
