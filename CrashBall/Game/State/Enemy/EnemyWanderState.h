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

	static constexpr float DIRECTION_CIRCLE_DISTANCE = 6.5f;	// 方向を決めるための円との距離

	static constexpr float DIRECTION_CIRCLE_RADIUS	 = 15.0f;	// 方向を決めるための円の半径

	static constexpr float WANDER_ACCELERATION = 30.0f;			// 徘徊の加速度

	// データメンバの宣言 -----------------------------------------------
private:

	float m_directionCircleRadian;	// 方向を決めるための円の角度

	float m_timer = 1.0f;

	DirectX::SimpleMath::Vector3 m_targetDirection;		// 目標の入力方向

	DirectX::SimpleMath::Vector3 m_currentDirection;	// 現在の入力方向

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	EnemyWanderState();

	// デストラクタ
	~EnemyWanderState();

	// 開始処理
	void OnEnter() override;

	// 更新処理
	void Update() override;

	// 終了処理
	void OnExit() override;


	// 操作
public:

	void AvoidWall(RigidBody* rigidbody, Transform* transform);

	// 取得/設定
public:

	// 内部実装
private:

};
