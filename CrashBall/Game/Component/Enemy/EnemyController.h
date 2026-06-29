/*****************************************************************//**
 * \file   EnemyController.h
 * \brief  敵操作コンポーネント
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"
#include "Game/State/StateMachine.h"
#include "Game/GameObject/Stage.h"

/**
 * \brief 敵操作コンポーネント
 */
class  EnemyController : public Component
{

	// パラメータの宣言 -------------------------------------------------
private:

	float m_acceleration;			// 加速度
	float m_avoidWallDistance;		// 壁を検知する距離
	float m_avoidWallWeakForce;		// 壁回避力(弱)
	float m_avoidWallStrongForce;	// 壁回避力(強)
	float m_maxHp;					// 最大体力

	// WarnderState
	float m_directionCircleDistance;	// 加速方向を決めるための円との距離
	float m_directionCircleRadius;		// 加速方向を決めるための円の半径
	float m_directionChageInterval;		// 加速方向を変える間隔

	// データメンバの宣言 -----------------------------------------------
private:

	std::unique_ptr<StateMachine<EnemyController>> m_stateMachine;	// ステートマシン

	Transform* m_transform			 = nullptr;		// トランスフォームコンポーネントのキャッシュ
	Rigidbody* m_rigidbody			 = nullptr;		// 物理演算コンポーネントのキャッシュ
	ModelRenderer* m_modelRenderer	 = nullptr;		// モデル描画コンポーネントのキャッシュ
	BallController* m_ballController = nullptr;		// ボール操作コンポーネントのキャッシュ

	DirectX::SimpleMath::Vector3 m_accelDirection;	// 加速行方向

	const IWallMeshGetter* m_wallMeshGetter = nullptr;	// 壁メッシュの取得クラス

	float m_hp = m_maxHp;	// 体力

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// デフォルトコンストラクタ
	EnemyController() = default;

	// コンストラクタ
	EnemyController(IGameObject* gameObject);

	// コピーコンストラクタ
	EnemyController(
		IGameObject* gameObject,
		const EnemyController& other);

	// ムーブコンストラクタ
	EnemyController(EnemyController&&) = default;

	// デストラクタ
	~EnemyController();

	// 操作
public:

	// 初期化
	void Initialize();

	// 更新
	void Update(const GameContext& gameContext);

	// ダメージ処理
	void Damage(float damage);

	// 取得/設定
public:

	// 加速方向の取得
	DirectX::SimpleMath::Vector3 GetAccelDirection() const { return m_accelDirection; }

	// 体力の取得
	float GetHp() const { return m_hp; }
	// 最大体力の取得
	float GetMaxHP() const { return m_maxHp; }

	// 加速方向を決めるための円との距離の取得
	float GetDirectionCircleDistance()	const { return m_directionCircleDistance; }
	// 加速方向を決めるための円の半径の取得
	float GetDirectionCircleRadius()	const { return m_directionCircleRadius; }
	// 加速方向を変える間隔の取得
	float GetDirectionChangeInterval()	const { return m_directionChageInterval; }

	// 加速方向の設定
	void SetAccelDirection(DirectX::SimpleMath::Vector3 direction) { m_accelDirection = direction; }

	// ステージのポインタの設定
	void SetFloor(IWallMeshGetter* meshGetter) { m_wallMeshGetter = meshGetter; }

	// 内部実装
private:

	// 壁回避
	void AvoidWall();

	// JsonConverter
private:

	friend void to_json(json& j, const EnemyController& enemyController);
	friend void from_json(const json& j, EnemyController& enemyController);

public:

	// 演算子オーバーロード
	void operator=(const EnemyController& other)
	{
		m_acceleration				= other.m_acceleration;
		m_avoidWallDistance			= other.m_avoidWallDistance;
		m_avoidWallWeakForce		= other.m_avoidWallWeakForce;
		m_avoidWallStrongForce		= other.m_avoidWallStrongForce;
		m_maxHp						= other.m_maxHp;
		m_directionCircleDistance	= other.m_directionCircleDistance;
		m_directionCircleRadius		= other.m_directionCircleRadius;
		m_directionChageInterval	= other.m_directionChageInterval;
	}

};
