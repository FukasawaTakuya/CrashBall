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

#include "FloorMeshGauge.h"
#include "PaintMeshBar.h"

/**
 * @brief ゲーム用のパネル
 */
class  GamePanel : public Panel {

	// クラス定数の宣言 -------------------------------------------------
private:

	// データメンバの宣言 -----------------------------------------------
private:

	UIContext m_uiContext;	// UI用のコンテキスト

	std::unique_ptr<FloorMeshGauge> m_floorMeshGauge;	// 現在の面の色を表すゲージ

	std::unique_ptr<PaintMeshBar> m_playerMeshBar;		// プレイヤーが塗った面を表示するバー

	std::unique_ptr<PaintMeshBar> m_enemyMeshBar;		// 敵が塗った面を表示するバー

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


		m_floorMeshGauge->GetComponent<FloorMeshGaugeController>()
			->SetContext(
				m_uiContext.floorMeshGetter,
				m_playerMeshBar.get(),
				m_enemyMeshBar.get()
			);

	}

	void SetSprite(const ResourceContext& resourceContext);

	// 内部実装
private:

};
