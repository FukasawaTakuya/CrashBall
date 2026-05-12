/*****************************************************************//**
 * \file   Enemy.h
 * \brief  敵オブジェクトに関するヘッダーファイル
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

// 多重インクルードの防止 =====================================================
#pragma once
// ヘッダファイルの読み込み ===================================================
#include "Game/GameObject/Ball.h"
#include "Game/State/StateMachine.h"

// クラスの前方宣言 ===================================================
class MeshFloor;


// クラスの定義 ===============================================================
/**
 * @brief 敵オブジェクト
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

	MeshFloor* m_pFloor = nullptr;							// 床のポインタ

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

	// 初期化処理
	void Inisitialize(DirectX::SimpleMath::Vector3 position);

	// 更新処理
	void Update();

	// 描画処理
	void Draw();


	// 取得/設定
public:

	// 加速方向の取得
	DirectX::SimpleMath::Vector3 GetAccelDirection() const { return m_accelDirection; }

	// 加速方向の設定
	void SetAccelDirection(DirectX::SimpleMath::Vector3 direction) { m_accelDirection = direction; }

	// 床のセット
	void SetFloor(MeshFloor* pFloor) { m_pFloor = pFloor; }

	// 床のポインタの取得
	MeshFloor* GetFloor() const { return m_pFloor; }


	// 内部実装
private:

	// 壁回避処理
	void AvoidWall();
};
