/*****************************************************************//**
 * \file   EnemyHpGaugeController.h
 * \brief  敵HPゲージ操作コンポーネント
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"
#include "Game/Component/Default/Renderer/TextRenderer.h"
#include "Game/Component/Default/Renderer/SpriteRenderer.h"
#include "Game/Common/Screen.h"
#include "Game/Component/Default/UI/SliderController.h"

/**
 * @brief 敵HPゲージ操作コンポーネント
 */
class  EnemyHpGaugeController : public Component {

	// データメンバの宣言 -----------------------------------------------
private:

	IGameObject* m_pEnemyHpGauge		= nullptr;	// 敵のHPゲージ
	IGameObject* m_pEnemyHpGaugeTrack	= nullptr;	// 敵のHPゲージの土台
	IGameObject* m_pEnemyHpText			= nullptr;	// 敵のHPの表示テキスト

	SliderController* m_enemyHpGaugeController = nullptr;	// HPゲージの操作コンポーネント
	TextRenderer* m_enemyHpTextRenderer		   = nullptr;	// テキストの描画コンポーネント

	int m_enemyHp = 0;		// 敵のHP
	int m_enemyMaxHp = 0;	// 敵の最大HP

	// プロパティの設定
	BeginProperty()
	EndProperty()

	// コンポーネント名の設定
	SetCompName("EnemyHpGaugeController")


	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	EnemyHpGaugeController(
		IGameObject* gameObject,
		IGameObject* pEnemyHpGauge,
		IGameObject* pEnemyHpGaugeTrack,
		IGameObject* pEnemyHpText
	);

	// デストラクタ
	~EnemyHpGaugeController();

	// 操作
public:

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 終了処理
	void Finalize();

	// 取得/設定
public:

	// UI表示に必要な数値の設定
	void SetUIValue(
		int enemyHp,
		int enemyMaxHp)
	{
		m_enemyHp = enemyHp;
		m_enemyMaxHp = enemyMaxHp;
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
