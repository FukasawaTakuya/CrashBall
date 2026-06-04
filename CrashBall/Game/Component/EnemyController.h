#pragma once

#include "Default/Component.h"
#include "Game/State/StateMachine.h"
#include "Game/GameObject/Stage.h"



/**
 * \brief 基底オブジェクト
 */
class  EnemyController : public Component{

	// クラス定数の宣言 -------------------------------------------------
private:

	static constexpr float ACCELERATINON = 37.0f;		// 加速度

	static constexpr float AVOID_WALL_DISTANCE = 5.0f;	// 壁回避の距離

	static constexpr float MAX_HP = 200.0f;				// 最大体力

	// データメンバの宣言 -----------------------------------------------
private:

	std::unique_ptr<StateMachine<EnemyController>> m_stateMachine;	// ステートマシン

	RigidBody* m_rigidbody = nullptr;				// 物理演算
	Transform* m_transform = nullptr;				// トランスフォーム
	BallController* m_ballController = nullptr;		// ボール管理

	DirectX::SimpleMath::Vector3 m_accelDirection;	// 進行方向

	const IWallMeshGetter* m_wallMeshGetter;		// 壁メッシュの取得クラス

	float m_hp;	// 体力

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	EnemyController(IGameObject* gameObject);

	// デストラクタ
	~EnemyController();

	// 操作
public:

	// 初期化
	void Initialize();

	// 更新
	void Update(const GameContext& gameContext);

	void Damage(float damage);

	// 取得/設定
public:

	// 加速方向の取得
	DirectX::SimpleMath::Vector3 GetAccelDirection() const { return m_accelDirection; }

	// 体力の取得
	float GetHp() const { return m_hp; }

	// 加速方向の設定
	void SetAccelDirection(DirectX::SimpleMath::Vector3 direction) { m_accelDirection = direction; }

	// ステージのポインタの設定
	void SetFloor(IWallMeshGetter* meshGetter) { m_wallMeshGetter = meshGetter; }

	// 内部実装
private:

	void AvoidWall();
};
