/*****************************************************************//**
 * \file   GamePanel.h
 * \brief  ゲーム用のパネル
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once

#include "Panel.h"

#include "Game/Context/UIContext.h"
#include "Game/Context/ResourceContext.h"

#include "Object2D.h"
#include "TextObject.h"

#include "Game/Component/FloorMeshGaugeController.h"
#include "Game/Component/AttackGaugeController.h"

 /**
  * @brief ゲーム用のパネル
  */
class  GamePanel : public Panel {

	// クラス定数の宣言 -------------------------------------------------
private:

	// データメンバの宣言 -----------------------------------------------
private:

	UIContext m_uiContext;	// UI用のコンテキスト

	// FloorMeshGaugeControllerで操作
	std::unique_ptr<Object2D>	m_playerMeshGauge;		// プレイヤーが塗った面を表示するゲージ
	std::unique_ptr<Object2D>	m_enemyMeshGauge;		// 敵が塗った面を表示するゲージ
	std::unique_ptr<Object2D>	m_gaugeTrack;			// ゲージの土台
	std::unique_ptr<Object2D>	m_gaugeBackGround;		// ゲージの背景
	std::unique_ptr<TextObject>	m_playerMeshNumText;	// プレイヤーのメッシュ数表示
	std::unique_ptr<TextObject>	m_enemyMeshNumText;		// 敵のメッシュ数表示

	// AttackGaugeControllerで操作
	std::unique_ptr<Object2D> m_attackGauge;		// 攻撃ゲージ
	std::unique_ptr<Object2D> m_attackGaugeTrack;	// 攻撃ゲージの土台


	// 床メッシュゲージ操作コンポーネントのキャッシュ
	FloorMeshGaugeController* m_floorMeshGaugeController = nullptr;
	// 攻撃ゲージ操作コンポーネントのキャッシュ
	AttackGaugeController* m_attackGaugeController = nullptr;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	GamePanel();

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


	// 取得/設定
public:

	// UI用のコンテキストの設定
	void SetUIContext(const UIContext& uiContext)
	{
		m_uiContext = uiContext;

		// ゲージに設定
		m_floorMeshGaugeController
			->SetFloorMeshGetter(
				m_uiContext.floorMeshGetter
			);

		m_attackGaugeController
			->SetFloorMeshGetter(
				m_uiContext.floorMeshGetter
			);
	}

	void SetSprite(const ResourceContext& resourceContext);

	// 内部実装
private:

};
