/*****************************************************************//**
 * \file   AttackGaugeController.h
 * \brief  攻撃ゲージ操作コンポーネント
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"
#include "Game/Component/Default/Renderer/SpriteRenderer.h"
#include "Game/Component/Default/Renderer/TextRenderer.h"
#include "Game/Common/Screen.h"
#include "Game/Component/Default/UI/SliderController.h"

#include "Game/ScriptableObject/ScriptableObject.h"


/**
 * @brief 攻撃ゲージ操作コンポーネント
 */
class  AttackGaugeController : public Component {
	
	// データメンバの宣言 -----------------------------------------------
private:

	IGameObject* m_pAttackGauge		  = nullptr;	// 攻撃ゲージ
	IGameObject* m_pAttackPowerText	  = nullptr;	// 攻撃力表示テキスト

	TextRenderer*	m_attackPowerTextRenderer	= nullptr;	// 攻撃力表示テキスト描画コンポーネントのキャッシュ
	SliderController* m_attackGaugeController	= nullptr;	// 攻撃ゲージの操作コンポーネントのキャッシュ

	int m_playerMeshCount	= 0;	// プレイヤーの面の数
	int m_playerAttackCost	= 0;	// プレイヤーの攻撃コスト
	int m_playerAttackPower = 0;	// プレイヤーの攻撃力

	const ScriptableObject* m_gameColor = nullptr;

	// プロパティの設定
	BeginProperty()
	EndProperty()

	// コンポーネント名の設定
	SetCompName("AttackGaugeController")


	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	AttackGaugeController(IGameObject* gameObject);

	// コンストラクタ
	AttackGaugeController(
		IGameObject* gameObejct,
		IGameObject* pAttackGauge,
		IGameObject* pAttackPowerText
	);

	// デストラクタ
	~AttackGaugeController();

	// 操作
public:

	// 初期化
	void Initilize();

	// 更新
	void Update();

	// 取得/設定
public:

	// UI表示に必要な数値の設定
	void SetUIValue(
		int playerMeshCount,
		int playerAttackCost,
		int playerAttackPower)
	{
		m_playerMeshCount	= playerMeshCount;
		m_playerAttackCost	= playerAttackCost;
		m_playerAttackPower	= playerAttackPower;
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
