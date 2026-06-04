/*****************************************************************//**
 * \file   PlayerAttackState.h
 * \brief  プレイヤー攻撃ステート 
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once

#include "PlayerStateBase.h"

/**
 * \brief プレイヤー攻撃ステート
 */
class  PlayerAttackState : public PlayerStateBase{

	// クラス定数の宣言 -------------------------------------------------
private:

	static constexpr float ATTACK_SPEED = 30.0f;	// 攻撃速度

	static constexpr float ATTACK_DURATION = 0.5f;	// 攻撃の持続時間

	// データメンバの宣言 -----------------------------------------------
private:

	float m_timer;		// タイマー

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	PlayerAttackState(const PlayerStateContext& stateContext);

	// デストラクタ
	~PlayerAttackState();

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
