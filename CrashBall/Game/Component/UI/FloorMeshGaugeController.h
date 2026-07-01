/*****************************************************************//**
 * \file   FloorMeshGaugeController.h
 * \brief  床メッシュゲージ操作コンポーネント
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"

#include "Game/Component/Default/Renderer/SpriteRenderer.h"
#include "Game/Component/Default/Physics/RectTransform.h"
#include "Game/Component/Default/Renderer/TextRenderer.h"

#include "Game/Common/Screen.h"
#include "Game/Component/Default/UI/SliderController.h"

/**
 * @brief 床メッシュゲージ操作コンポーネント
 */
class  FloorMeshGaugeController : public Component {

	// クラス定数の宣言 -------------------------------------------------
private:

	float GAUGE_SLIDE_SPEED = 5.0f;		// ゲージがスライドする速さ

	// データメンバの宣言 -----------------------------------------------
private:

	// 管理ゲームオブジェクト
	IGameObject* m_pPalyerMeshGauge		= nullptr;	// プレイヤーが塗った面のゲージ
	IGameObject* m_pEnemyMeshGauge		= nullptr;	// 敵が塗った面のゲージ
	IGameObject* m_pPlayerMeshNumText	= nullptr;	// プレイヤーのメッシュ数表示
	IGameObject* m_pEnemyMeshNumText	= nullptr;	// 敵のメッシュ数表示

	// ゲージのコンポーネントのキャッシュ
	SliderController* m_playerGaugeController	= nullptr;
	SliderController* m_enemyGaugeController	= nullptr;

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