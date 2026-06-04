/*****************************************************************//**
 * \file   PlayerStatusController.h
 * \brief  プレイヤーステータス管理コンポーネント
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once

#include "Default/Component.h"
#include "IFloorMeshGetter.h"

/**
 * @brief プレイヤーステータス管理コンポーネント
 */
class  PlayerStatusController: public Component {

	// クラス定数の宣言 -------------------------------------------------
private:

	static constexpr float ATTACK_PER_FACE = 1.0f;		// 塗った面１枚当たりの上昇攻撃力

	static constexpr float MAX_ATTACK_POWER = 80.0f;	// 最大攻撃力

	static constexpr int ATTACK_REQUIRED_FACE = 20;		// 攻撃可能ボーダー

	// データメンバの宣言 -----------------------------------------------
private:

	float m_attackPower = 0;	// 攻撃力

	IFloorMeshGetter* m_floorMeshGetter = nullptr;	// 床メッシュ取得コンポーネント

	bool m_canAttack = false;	// 攻撃可能かどうか


	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	PlayerStatusController(IGameObject* gameObject);

	// デストラクタ
	~PlayerStatusController();

	// 操作
public:

	// 更新
	void Update();

	// 攻撃力を求める
	void CalcAttackPower();

	// 取得/設定
public:

	// 攻撃力の取得
	float GetAttackPower() const { return m_attackPower; }

	// 攻撃可能か取得
	bool GetCanAttack() const { return m_canAttack; }

	// 床メッシュ取得コンポーネントを設定 
	void SetFloorMeshGetter(IFloorMeshGetter* floorMeshGetter)
	{
		m_floorMeshGetter = floorMeshGetter;
	}

	// 内部実装
private:

};
