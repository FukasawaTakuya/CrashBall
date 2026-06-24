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

	// クラス定数の宣言 -------------------------------------------------
private:

	static constexpr float MIN_ATTACK_POWER = 10.0f;	// 最低攻撃力

public:

	static constexpr int ATTACK_COST = 20;	// 攻撃コスト

	int m_ATTACK_COST = 10.f;
	float m_MIN_ATTACK_POWER = 20;

	// データメンバの宣言 -----------------------------------------------
private:

	float m_attackPower = 0;	// 攻撃力

	IFloorMeshGetter* m_floorMeshGetter = nullptr;	// 床メッシュ取得コンポーネント

	bool m_canAttack = false;	// 攻撃可能かどうか

	bool m_isAttack = false;	// 攻撃中かどうか


	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

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
	int GetAttacckCost() const { return ATTACK_COST; }

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

};
