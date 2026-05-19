/*****************************************************************//**
 * \file   Enemy.h
 * \brief  敵クラス
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once

#include "Game/GameObject/Ball.h"
#include "Game/State/StateMachine.h"

class Stage;


/**
 * @brief 敵クラス
 */
class  Enemy : public Ball 
{
	// クラス定数の宣言 -------------------------------------------------
private:

	static constexpr float ACCELERATINON = 30.0f;		// 加速度

	static constexpr float AVOID_WALL_DISTANCE = 6.0f;	// 壁回避の距離

	// データメンバの宣言 -----------------------------------------------
private:

	std::unique_ptr<StateMachine<Enemy>> m_stateMachine;	// ステートマシン

	DirectX::SimpleMath::Vector3 m_accelDirection;			// 進行方向

	Stage* m_pStage = nullptr;								// ステージのポインタ

	DirectX::SimpleMath::Vector3 m_debugDirection;			// デバッグ用の方向ベクトル

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Enemy(float radius);

	// デストラクタ
	~Enemy();

	// 操作
public:

	// 初期化
	void Initialize() override;

	// 更新
	void Update(const GameContext& gameContext) override;

	// 描画
	void Render(const GameContext& gameContext) override;

	// 終了処理
	void Finalize() override;

	// 取得/設定
public:

	// 加速方向の取得
	DirectX::SimpleMath::Vector3 GetAccelDirection() const { return m_accelDirection; }

	// ステージのポインタの取得
	Stage* GetFloor() const { return m_pStage; }

	// 加速方向の設定
	void SetAccelDirection(DirectX::SimpleMath::Vector3 direction) { m_accelDirection = direction; }

	// ステージのポインタの設定
	void SetFloor(Stage* pFloor) { m_pStage = pFloor; }

	// 内部実装
private:

	// 壁回避
	void AvoidWall();
};
