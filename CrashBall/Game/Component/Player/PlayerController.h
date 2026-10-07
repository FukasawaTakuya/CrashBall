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
#include "Game/Component/Camera/TargetCameraController.h"
#include "Game/Component/Stage/IPaintConsumer.h"
#include "Game/Component/Stage/StageController.h"

/**
 * \brief プレイヤー操作コンポーネント
 */
class  PlayerController : public Component {

	// メンバ変数宣言 -----------------------------------------------
private:

	// AttackState
	float m_attackSpeed;		// 攻撃速度
	float m_attackDuration;		// 攻撃の持続時間
	float m_hitStopTime;		// ヒットストップ時間
	// MoveState
	float m_acceleration;	// 加速度 
	float m_maxSpeed;		// 最大速度

	const Transform* m_pEnemyTransform	= nullptr;	// 敵のトランスフォームコンポーネント
	const Camera*	 m_pCamera			= nullptr;	// カメラのポインタ
	StageController* m_pStageController = nullptr;	// 面消費用

	std::unique_ptr<StateMachine<PlayerController>> m_stateMachine;	// ステートマシン

	// プロパティの設定
	BeginProperty()
		AddProperty(m_attackSpeed,			PropertyType::Float)
		AddProperty(m_attackDuration,		PropertyType::Float)
		AddProperty(m_hitStopTime,			PropertyType::Float)
		AddProperty(m_acceleration,			PropertyType::Float)
		AddProperty(m_maxSpeed,				PropertyType::Float)
		AddProperty(m_pEnemyTransform,		PropertyType::Component)
		AddProperty(m_pCamera,				PropertyType::Component)
		AddProperty(m_pStageController,		PropertyType::Component)
	EndProperty()

	// コンポーネント名の設定
	SetCompName("PlayerController")

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	PlayerController(IGameObject* gameObject);

	// デストラクタ
	~PlayerController() = default;

	// 操作
public:

	// アタッチ時の処理
	void Awake() override;

	// 開始処理
	void Start(const GameContext& gameContext) override;

	// 更新
	void Update(const GameContext& gameContext) override;

	// 取得/設定
public:

	// カメラのポインタの取得
	const Camera* GetCamera() 
	{ 
		return m_pCamera; 
	}

	// 敵のトランスフォームの取得
	const Transform* GetEnemyTransform()
	{ 
		return m_pEnemyTransform; 
	}
	
	// 面消費インターフェースの取得
	IPaintConsumer* GetPaintConsumer() const
	{
		return m_pStageController;
	}

	// 攻撃速度の取得
	float GetAttackSpeed()		const { return m_attackSpeed; }
	// 攻撃持続時間の取得
	float GetAttackDuration()	const { return m_attackDuration; }
	// ヒットストップ時間の取得
	float GetHitStopTime()		const { return m_hitStopTime; }
	// 移動時の加速度の取得
	float GetAcceleration()		const { return m_acceleration; }
	// 最大移動速度の取得
	float GetMaxSpeed()			const { return m_maxSpeed; }

	// カメラのポインタのセット
	void SetCamera(const Camera* pCamera) { m_pCamera = pCamera; }

	// 敵のトランスフォームの設定
	void SetEnemyTransform(Transform* enemyTransform)
	{
		m_pEnemyTransform = enemyTransform;
	}

	// 内部実装
private:

	// プロパティの取得
	virtual const std::vector<PropertyInfo>& GetProperties() const override
	{
		return m_properties;
	}

	// コンポーネント名の取得
	virtual std::string GetCompName() const override
	{
		return m_compName;
	}
};
