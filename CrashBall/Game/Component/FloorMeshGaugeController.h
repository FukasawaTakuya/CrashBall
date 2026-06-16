/*****************************************************************//**
 * \file   FloorMeshGaugeController.h
 * \brief  
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"

#include "Default/SpriteRenderer.h"
#include "Default/RectTransform.h"
#include "Default/TextRenderer.h"

#include "IFloorMeshGetter.h"

#include "Game/Context/GameContext.h"
#include "Game/Context/RenderContext.h"

#include "Game/Common/Screen.h"

/**
 * @brief 
 */
class  FloorMeshGaugeController : public Component {

	// クラス定数の宣言 -------------------------------------------------
private:

	static constexpr DirectX::SimpleMath::Vector2 POSITION 
		= { Screen::CENTER_X, Screen::HEIGHT - 50.0f };	// 描画位置

	float GAUGE_LAYER_DEPTH = 0.2f;		// ゲージの描画順

	// データメンバの宣言 -----------------------------------------------
private:


	IFloorMeshGetter* m_floorMeshGetter = nullptr;	// 床メッシュ取得コンポーネント

	// 管理ゲームオブジェクト
	IGameObject* m_pPalyerMeshGauge		= nullptr;	// プレイヤーが塗った面のゲージ
	IGameObject* m_pEnemyMeshGauge		= nullptr;	// 敵が塗った面のゲージ
	IGameObject* m_pGaugeTrack			= nullptr;	// ゲージの土台
	IGameObject* m_pGaugeBackGround		= nullptr;	// ゲージの背景
	IGameObject* m_pPlayerMeshNumText	= nullptr;	// プレイヤーのメッシュ数表示
	IGameObject* m_pEnemyMeshNumText	= nullptr;	// 敵のメッシュ数表示

	// ゲージのコンポーネントのキャッシュ
	SpriteRenderer* m_playerGaugeRenderer	= nullptr;
	SpriteRenderer* m_enemyGaugeRenderer	= nullptr;
	RectTransform* m_playerGaugeTransform	= nullptr;
	RectTransform* m_enemyGaugeTransform	= nullptr;

	// 土台のコンポーネントのキャッシュ
	SpriteRenderer* m_gaugeTrackRenderer = nullptr;
	RectTransform* m_gaugeTrackTransform = nullptr;

	// テキストのコンポーネントのキャッシュ
	TextRenderer* m_playerTextRenderer = nullptr;
	TextRenderer* m_enemyTextRenderer  = nullptr;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	FloorMeshGaugeController(
		IGameObject* gameObject,		
		IGameObject* pPalyerMeshGauge,
		IGameObject* pEnemyMeshGauge,
		IGameObject* pGaugeTrack,	
		IGameObject* pGaugeBackGround,
		IGameObject* pPlayerMeshNumText,
		IGameObject* pEnemyMeshNumText
		);

	// デストラクタ
	~FloorMeshGaugeController();

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

	//  床メッシュ取得コンポーネントの設定
	void SetFloorMeshGetter(IFloorMeshGetter* floorMeshGetter)
	{
		m_floorMeshGetter = floorMeshGetter;
	}

	// 内部実装
private:

};