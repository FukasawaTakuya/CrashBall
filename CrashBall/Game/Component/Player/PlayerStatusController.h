/*****************************************************************//**
 * \file   PlayerStatusController.h
 * \brief  プレイヤーステータス管理コンポーネント
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"
#include "Game/Component/Stage/StageController.h"

/**
 * @brief プレイヤーステータス管理コンポーネント
 */
class  PlayerStatusController: public Component {

	// メンバ変数の宣言 -----------------------------------------------
private:

	float m_attackPower = 0;	// 攻撃力
	bool m_canAttack = false;	// 攻撃可能フラグ
	bool m_isAttack  = false;	// 攻撃中フラグ

	int m_attackCost		= 0;	// 攻撃コスト
	float m_minAttackPower	= 0.0f;	// 最低攻撃力
	float m_powerUpRate		= 1.0f;	// 強化倍率

	const StageController* m_pFloorMeshGetter = nullptr;	// 床メッシュ取得コンポーネント

	// プロパティの設定
	BeginProperty()
		AddProperty(m_attackCost, PropertyType::Int)
		AddProperty(m_minAttackPower, PropertyType::Float)
		AddProperty(m_powerUpRate, PropertyType::Float)
		AddProperty(m_pFloorMeshGetter, PropertyType::Component)
	EndProperty()

	// コンポーネント名の設定
	SetCompName("PlayerStatusController")

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	PlayerStatusController(IGameObject* gameObject);

	// デストラクタ
	~PlayerStatusController() = default;

	// 操作
public:

	// 更新
	void Update(const GameContext& gameContext) override;

	// 取得/設定
public:

	// 攻撃力の取得
	float GetAttackPower() const { return m_attackPower; }

	// 攻撃可能か取得
	bool GetCanAttack() const { return m_canAttack; }

	// 攻撃コストを取得
	int GetAttacckCost() const { return m_attackCost; }

	// 攻撃中フラグを設定
	void SetIsAttack(bool isAttack)
	{
		m_isAttack = isAttack;
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
