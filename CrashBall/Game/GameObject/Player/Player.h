/*****************************************************************//**
 * \file   Player.h
 * \brief  プレイヤークラス 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "Game/GameObject/Ball.h"
#include "Game/State/StateMachine.h"
#include "Game/Component/PlayerController.h"

class Camera;

/**
 * \brief プレイヤークラス
 */
class  Player : public Ball{

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	PlayerController* m_playerController;	// プレイヤー操作

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Player(float radius);

	// デストラクタ
	~Player() = default;

	// 操作
public:

	// 初期化
	void Initialize() override;

	// 更新
	void Update(const GameContext& gameContext) override;

	// 描画
	void Render(const RenderContext& renderContext) override;

	// 終了処理
	void Finalize() override;

	// 取得/設定
public:

	// 内部実装
private:

};
