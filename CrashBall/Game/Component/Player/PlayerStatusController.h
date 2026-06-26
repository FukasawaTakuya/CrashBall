/*****************************************************************//**
 * \file   PlayerStatusController.h
 * \brief  プレイヤーステータス管理コンポーネント
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once

#include "../Default/Component.h"
#include "../Stage/IFloorMeshGetter.h"

/**
 * @brief プレイヤーステータス管理コンポーネント
 */
class  PlayerStatusController: public Component {

	// パラメータの宣言 -------------------------------------------------
private:

	int m_attackCost		 = 0;		// 攻撃コスト
	float m_minAttackPower	= 0.0f;		// 最低攻撃力

	// データメンバの宣言 -----------------------------------------------
private:

	float m_attackPower = 0;	// 攻撃力

	IFloorMeshGetter* m_floorMeshGetter = nullptr;	// 床メッシュ取得コンポーネント

	bool m_canAttack = false;	// 攻撃可能かどうか

	bool m_isAttack = false;	// 攻撃中かどうか


	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	PlayerStatusController() = default;

	// コンストラクタ
	PlayerStatusController(IGameObject* gameObject);

	// コピーコンストラクタ
	PlayerStatusController(
		IGameObject* gameObject,
		const PlayerStatusController& playerStatusController
	);

	// デストラクタ
	~PlayerStatusController();

	// 操作
public:

	// 更新
	void Update();

	// 取得/設定
public:

	// 攻撃力の取得
	float GetAttackPower() const { return m_attackPower; }

	// 攻撃可能か取得
	bool GetCanAttack() const { return m_canAttack; }

	// 攻撃コストを取得
	int GetAttacckCost() const { return m_attackCost; }

	// 床メッシュ取得コンポーネントを設定 
	void SetFloorMeshGetter(IFloorMeshGetter* floorMeshGetter)
	{
		m_floorMeshGetter = floorMeshGetter;
	}

	void SetIsAttack(bool isAttack)
	{
		m_isAttack = isAttack;
	}

	// 内部実装
private:

	// JsonConverter
private:

	friend void from_json(const json& j, PlayerStatusController& playerStatusController);
	friend void to_json(json& j, const PlayerStatusController& playerStatusController);

public:
	// 演算子オーバーロード
	void operator=(const PlayerStatusController& statusController)
	{
		m_attackCost = statusController.m_attackCost;
		m_minAttackPower = statusController.m_minAttackPower;
	}
};
