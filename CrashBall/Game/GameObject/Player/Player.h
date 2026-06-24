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
#include "Game/Component/Player/PlayerController.h"
#include "Game/Component/Player/PlayerStatusController.h"

/**
 * \brief プレイヤークラス
 */
class  Player : public Ball {

	// クラス定数の宣言 -------------------------------------------------
private:

	static constexpr float RADIUS = 20.0f;	// 半径
	static constexpr float SCALE = 0.025f;	// スケール
	
	// データメンバの宣言 -----------------------------------------------
private:

	// コンポーネントのキャッシュ
	PlayerController*		m_playerController;			// プレイヤー操作
	PlayerStatusController* m_playerStatusController;	// プレイヤーステータス操作

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Player();

	//
	//Player(json data);

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
