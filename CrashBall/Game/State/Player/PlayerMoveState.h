/*****************************************************************//**
 * \file   PlayerMoveState.h
 * \brief  プレイヤー移動ステート 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "PlayerStateBase.h"
#include "Game/Common/Easing.h"

/**
 * \brief プレイヤー移動ステート
 */
class  PlayerMoveState : public PlayerStateBase {

	// メンバ変数の宣言 -----------------------------------------------
private:

	Easing<DirectX::SimpleMath::Color> m_ambient;

	// ターゲットカメラ操作
	TargetCameraController* m_targetCameraController;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	PlayerMoveState(const PlayerStateContext& stateContext);

	// デストラクタ
	~PlayerMoveState();

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
