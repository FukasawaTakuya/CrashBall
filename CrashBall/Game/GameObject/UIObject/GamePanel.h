/*****************************************************************//**
 * \file   GamePanel.h
 * \brief  ゲーム用のパネル
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once

#include "Panel.h"

#include "Game/Context/ResourceContext.h"

#include "Object2D.h"
#include "TextObject.h"

#include "Game/Component/UI/FloorMeshGaugeController.h"
#include "Game/Component/UI/AttackGaugeController.h"
#include "Game/Component/UI/EnemyHpGaugeController.h"

 /**
  * @brief ゲーム用のパネル
  */
class  GamePanel : public Panel {

	// クラス定数の宣言 -------------------------------------------------
private:

	// データメンバの宣言 -----------------------------------------------
private:

	// FloorMeshGaugeControllerで操作
	std::unique_ptr<Object2D>	m_playerMeshGauge;		// プレイヤーが塗った面を表示するゲージ
	std::unique_ptr<Object2D>	m_enemyMeshGauge;		// 敵が塗った面を表示するゲージ
	std::unique_ptr<Object2D>	m_gaugeTrack;			// ゲージの土台
	std::unique_ptr<Object2D>	m_gaugeBackGround;		// ゲージの背景
	std::unique_ptr<TextObject>	m_playerMeshNumText;	// プレイヤーのメッシュ数表示テキスト
	std::unique_ptr<TextObject>	m_enemyMeshNumText;		// 敵のメッシュ数表示テキスト

	// AttackGaugeControllerで操作
	std::unique_ptr<Object2D> m_attackGauge;		// 攻撃ゲージ
	std::unique_ptr<Object2D> m_attackGaugeTrack;	// 攻撃ゲージの土台
	std::unique_ptr<TextObject> m_attackPowerText;	// 攻撃力表示テキスト

	// EnemyHpGaugeControllerで操作
	std::unique_ptr<Object2D> m_enemyHpGauge;		// 敵のHPゲージ
	std::unique_ptr<Object2D> m_enemyHpGaugeTrack;	// 敵のHPゲージの土台
	std::unique_ptr<TextObject> m_enemyHpText;		// 敵のHP表示テキスト

	// 床メッシュゲージ操作コンポーネントのキャッシュ
	FloorMeshGaugeController* m_floorMeshGaugeController = nullptr;
	// 攻撃ゲージ操作コンポーネントのキャッシュ
	AttackGaugeController* m_attackGaugeController = nullptr;
	// 敵HP操作コンポーネントのキャッシュ
	EnemyHpGaugeController* m_enemyHpGaugeController = nullptr;

	// UI表示に必要な数値
	int m_playerMeshCount	= 0;	// プレイヤーの面の数
	int m_enemyMeshCount	= 0;	// 敵の面の数
	int m_totalMeshCount	= 0;	// 全体の面の数
	int m_playerAttackCost	= 0;	// プレイヤーの攻撃コスト
	int m_playerAttackPower = 0;	// プレイヤーの攻撃力
	int m_enemyHp			= 0;	// 敵のHp
	int m_enemyMaxHp		= 0;	// 敵の最大HP

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	GamePanel();

	GamePanel(json* data);

	// デストラクタ
	~GamePanel();

	// 操作
public:

	// 初期化
	void Initialize();

	// 更新
	void Update(const GameContext& gameContext);

	// 描画
	void Render(const RenderContext& renderContext);

	// 終了処理
	void Finalize();

	// パラメータの書き込み
	void SaveParam() override;

	// 初期化用のパラメータの書き込み
	void SaveInitParam() override;

	// データの再読み込み
	void ReloadParam() override;


	// 取得/設定
public:

	// UI表示に必要な数値を設定
	void SetUIValue(
		int playerMeshCount,
		int enemyMeshCount,
		int totalMeshCount,
		int playerAttackCost,
		int playerAttackPower,
		int enemyHp,
		int enemyMaxHp
	)
	{
		m_playerMeshCount	= playerMeshCount;
		m_enemyMeshCount	= enemyMeshCount;
		m_totalMeshCount	= totalMeshCount;
		m_playerAttackCost  = playerAttackCost;
		m_playerAttackPower	= playerAttackPower;
		m_enemyHp			= enemyHp;
		m_enemyMaxHp		= enemyMaxHp;
	}

	void SetSprite(const ResourceContext& resourceContext);

	// 内部実装
private:

};
