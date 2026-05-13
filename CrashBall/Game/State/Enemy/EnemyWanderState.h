/*****************************************************************//**
 * \file   EnemyWanderState.h
 * \brief  敵の徘徊ステートに関するヘッダーファイル
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

// 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include "Game/State/StateBase.h"

// クラスの前方宣言 ===================================================
class Enemy;


// クラスの定義 ===============================================================
/**
 * @brief 敵徘徊ステート
 */
class  EnemyWanderState : public StateBase<Enemy> {

	// クラス定数の宣言 -------------------------------------------------
private:

	static constexpr float DIRECTION_CIRCLE_DISTANCE = 4.5f;	// 方向を決めるための円との距離

	static constexpr float DIRECTION_CIRCLE_RADIUS	 = 10.0f;	// 方向を決めるための円の半径

	static constexpr float DIRECTION_CHANGE_INTERVAL = 1.5f;	// 方向を変える間隔

	// データメンバの宣言 -----------------------------------------------
private:

	float m_directionCircleRadian;						// 方向を決めるための円の角度

	float m_timer = DIRECTION_CHANGE_INTERVAL;			// 

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	EnemyWanderState();

	// デストラクタ
	~EnemyWanderState();

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
