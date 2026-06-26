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
class  EnemyController : public Component{

	// パラメータの宣言 -------------------------------------------------
private:

	float m_acceleration = 37.0f;			// 加速度
	float m_avoidWallDistance = 5.0f;		// 壁を検知する距離
	float m_avoidWallWeakForce = 0.7f;		// 壁回避力(弱)
	float m_avoidWallStrongkForce = 0.7f;	// 壁回避力(強)
	float m_maxHp = 200.0f;					// 最大体力

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
	//EnemyController(
	//	IGameObject* gameObject,
	//	const EnemyController& other);

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

	// 加速方向の設定
	void SetAccelDirection(DirectX::SimpleMath::Vector3 direction) { m_accelDirection = direction; }

	// ステージのポインタの設定
	void SetFloor(IWallMeshGetter* meshGetter) { m_wallMeshGetter = meshGetter; }

	// 内部実装
private:

	// 壁回避
	void AvoidWall();
};
