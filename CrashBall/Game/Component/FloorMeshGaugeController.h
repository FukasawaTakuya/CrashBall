/*****************************************************************//**
 * \file   FloorMeshGaugeController.h
 * \brief  床メッシュゲージ操作コンポーネント
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"

#include "Default/SpriteRenderer.h"
#include "Default/RectTransform.h"
#include "Default/TextRenderer.h"

#include "Game/Common/Screen.h"

/**
 * @brief 床メッシュゲージ操作コンポーネント
 */
class  FloorMeshGaugeController : public Component {

	// クラス定数の宣言 -------------------------------------------------
private:

	// ゲージの描画位置
	static constexpr DirectX::SimpleMath::Vector2 GAUGE_POSITION 
		= { Screen::CENTER_X, Screen::HEIGHT - 50.0f };	

	// ゲージの土台のスケール
	static constexpr DirectX::SimpleMath::Vector2 BACKGROUND_SCALE
		= DirectX::SimpleMath::Vector2(1.1f, 3.5f);

	// プレイヤーのメッシュ数表示テキストの描画位置
	static constexpr DirectX::SimpleMath::Vector2 PLAYER_MESHTEXT_POSITION
		= DirectX::SimpleMath::Vector2(Screen::CENTER_X - 250.0f, Screen::HEIGHT - 95.0f);

	// 敵のメッシュ数表示テキストの描画位置
	static constexpr DirectX::SimpleMath::Vector2 ENEMY_MESHTEXT_POSITION
		= DirectX::SimpleMath::Vector2(Screen::CENTER_X + 250.0f, Screen::HEIGHT - 95.0f);

	float TEXT_FONTSCALE = 0.75f;		// テキストのフォントスケール
	float GAUGE_LAYER_DEPTH = 0.2f;		// ゲージの描画順
	float TRACK_LAYER_DEPTH = 0.1f;		// ゲージの土台の描画順
	float GAUGE_SLIDE_SPEED = 5.0f;		// ゲージがスライドする速さ

	// データメンバの宣言 -----------------------------------------------
private:

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

	int m_playerMeshCount = 0;	// プレイヤーの面の数
	int m_enemyMeshCount = 0;	// 敵の面の数
	int m_totalMeshCount = 0;	// 全体の面の数

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
	void Update();

	// 終了処理
	void Finalize();

	// 取得/設定
public:

	// UI表示に必要な数値を設定
	void SetUIValue(
		int playerMeshCount,
		int enemyMeshCount,
		int totalMeshCount
	)
	{
		m_playerMeshCount = playerMeshCount;
		m_enemyMeshCount  = enemyMeshCount;
		m_totalMeshCount  = totalMeshCount;
	}

	// 内部実装
private:

};