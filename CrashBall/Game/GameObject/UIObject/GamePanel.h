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
#include "Slider.h"

#include "Game/Component/UI/FloorMeshGaugeController.h"
#include "Game/Component/UI/AttackGaugeController.h"
#include "Game/Component/UI/EnemyHpGaugeController.h"

 /**
  * @brief ゲーム用のパネル
  */
class  GamePanel : public Panel {

	// データメンバの宣言 -----------------------------------------------
private:

	// FloorMeshGaugeControllerで操作
	std::unique_ptr<Slider>		m_playerMeshGauge;		// プレイヤーが塗った面を表示するゲージ
	std::unique_ptr<Slider>		m_enemyMeshGauge;		// 敵が塗った面を表示するゲージ
	std::unique_ptr<Object2D>	m_meshGaugeTrack;		// ゲージの土台
	std::unique_ptr<Object2D>	m_gaugeBackGround;		// ゲージの背景
	std::unique_ptr<TextObject>	m_playerMeshNumText;	// プレイヤーのメッシュ数表示テキスト
	std::unique_ptr<TextObject>	m_enemyMeshNumText;		// 敵のメッシュ数表示テキスト

	// AttackGaugeControllerで操作
	std::unique_ptr<Slider> m_attackGauge;			// 攻撃ゲージ
	std::unique_ptr<Object2D> m_attackGaugeTrack;	// 攻撃ゲージの土台
	std::unique_ptr<TextObject> m_attackPowerText;	// 攻撃力表示テキスト

	// EnemyHpGaugeControllerで操作
	std::unique_ptr<Slider> m_enemyHpGauge;			// 敵のHPゲージ
	std::unique_ptr<Object2D> m_enemyHpGaugeTrack;	// 敵のHPゲージの土台
	std::unique_ptr<TextObject> m_enemyHpText;		// 敵のHP表示テキスト

	// 床メッシュゲージ操作コンポーネントのキャッシュ
	FloorMeshGaugeController* m_floorMeshGaugeController = nullptr;
	// 攻撃ゲージ操作コンポーネントのキャッシュ
	AttackGaugeController* m_attackGaugeController = nullptr;
	// 敵HP操作コンポーネントのキャッシュ
	EnemyHpGaugeController* m_enemyHpGaugeController = nullptr;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	GamePanel(ordered_json* data);

	// デストラクタ
	~GamePanel();

	// 操作
public:

	// 初期化
	void Start(const GameContext& gameContext) override;

	// 更新
	void Update(const GameContext& gameContext) override;

	// 描画
	void Render(const RenderContext& renderContext) override;

	// 取得/設定
public:

	void SetSprite(const ResourceContext& resourceContext);

	// 内部実装
private:

};
