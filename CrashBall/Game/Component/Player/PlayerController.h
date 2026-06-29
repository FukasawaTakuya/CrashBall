/*****************************************************************//**
 * \file   PlayerController.h
 * \brief  プレイヤー操作コンポーネント
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"

#include "PlayerStatusController.h"
#include "Game/State/StateMachine.h"
#include "Game/Component/Camera/TargetCamera.h"
#include "Game/Component/Stage/IPaintConsumer.h"
#include "Game/Component/Stage/StageController.h"

class PlayerStateBase;

/**
 * \brief プレイヤー操作コンポーネント
 */
class  PlayerController : public Component {

	// パラメータの宣言 -------------------------------------------------
private:

	// AttackState
	float m_attackSpeed = 0.0f;		// 攻撃速度
	float m_attackDuration = 0.0f;	// 攻撃の持続時間
	// MoveState
	float m_acceleration = 0.0f;	// 加速度 
	float m_maxSpeed = 0.0f;		// 最大速度

	// データメンバの宣言 -----------------------------------------------
private:

	std::unique_ptr<StateMachine<PlayerController>> m_stateMachine;	// ステートマシン

	const ICamera* m_pCamera = nullptr;				// カメラのポインタ

	const Transform* m_enemyTransform = nullptr;	// 敵のトランスフォームコンポーネント

	IPaintConsumer* m_paintConsumer = nullptr;		// 面消費インターフェース

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// デフォルトコンストラクタ
	PlayerController() = default;

	// コンストラクタ
	PlayerController(IGameObject* gameObject);

	// コピーコンストラクタ
	PlayerController(
		IGameObject* gameObject,
		const PlayerController& other);

	// ムーブコンストラクタ
	PlayerController(PlayerController&&) = default;

	// デストラクタ
	~PlayerController();

	// 操作
public:

	// 初期化
	void Initialize();

	// 更新
	void Update(const GameContext& gameContext);

	// 取得/設定
public:

	// カメラのポインタの取得
	const ICamera* GetCamera() 
	{ 
		return m_pCamera; 
	}

	// 敵のトランスフォームの取得
	const Transform* GetEnemyTransform()
	{ 
		return m_enemyTransform; 
	}
	
	// 面消費インターフェースの取得
	IPaintConsumer* GetPaintConsumer() const
	{
		return m_paintConsumer;
	}

	// パラメータの取得
	// 攻撃速度の取得
	float GetAttackSpeed()		const { return m_attackSpeed; }
	// 攻撃持続時間の取得
	float GetAttackDuration()	const { return m_attackDuration; }
	// 移動時の加速度の取得
	float GetAcceleration()		const { return m_acceleration; }
	// 最大移動速度の取得
	float GetMaxSpeed()			const { return m_maxSpeed; }

	// カメラのポインタのセット
	void SetCamera(const TargetCamera* pCamera) { m_pCamera = pCamera; }

	// 敵のトランスフォームの設定
	void SetEnemyTransform(Transform* enemyTransform)
	{
		m_enemyTransform = enemyTransform;
	}

	// ステージ操作コンポーネントからインターフェースを設定する
	void SetStageInterface(StageController* stageController)
	{
		// 面消費コンポーネントの設定
		m_paintConsumer = stageController;
		// 床メッシュ取得コンポーネントを設定
		GetGameObject()->GetComponent<PlayerStatusController>()->SetFloorMeshGetter(stageController);
	}

	// 内部実装
private:

	// ステートの取得
	template<typename State>
	PlayerStateBase* GetState() const
	{
		return m_stateMachine->GetState<State>();
	}

	// JsonConvert
private:
	friend void to_json(json& j, const PlayerController& playerController);
	friend void from_json(const json& j, PlayerController& playerController);

public:

	// 演算子オーバーロード
	void operator=(const PlayerController& other)
	{
		m_attackSpeed		= other.m_attackSpeed;
		m_attackDuration	= other.m_attackDuration;
		m_acceleration		= other.m_acceleration;
		m_maxSpeed			= other.m_maxSpeed;
	}
};
