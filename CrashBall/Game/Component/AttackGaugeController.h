/*****************************************************************//**
 * \file   AttackGaugeController.h
 * \brief  攻撃ゲージ操作コンポーネント
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"
#include "Game/GameObject/IGameObject.h"
#include "Game/Context/GameContext.h"
#include "Default/SpriteRenderer.h"
#include "Game/Common/Screen.h"


/**
 * @brief 攻撃ゲージ操作コンポーネント
 */
class  AttackGaugeController : public Component {

	// クラス定数の宣言 -------------------------------------------------
private:

	// 攻撃ゲージの描画位置
	static constexpr DirectX::SimpleMath::Vector2
		GAUGE_POSITION = DirectX::SimpleMath::Vector2(Screen::CENTER_X, Screen::CENTER_Y + 150.f);


	// データメンバの宣言 -----------------------------------------------
private:

	IGameObject* m_pAttackGauge		  = nullptr;	// 攻撃ゲージ
	IGameObject* m_pAttackGaugeTrack  = nullptr;	// 攻撃ゲージの土台

	SpriteRenderer* m_gaugeRenderer = nullptr;		// ゲージの描画コンポーネントのキャッシュ

	int m_playerMeshCount = 0;	// プレイヤーの面の数
	int m_playerAttackCost = 0;	// プレイヤーの攻撃コスト

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	AttackGaugeController(
		IGameObject* gameObejct,
		IGameObject* pAttackGauge,
		IGameObject* pAttackGaugeTrack
	);

	// デストラクタ
	~AttackGaugeController();

	// 操作
public:

	// 初期化
	void Initilize();

	// 更新
	void Update(const GameContext& gameContext);

	// 取得/設定
public:

	// UI表示に必要な数値の設定
	void SetUIValue(
		int playerMeshCount,
		int playerAttackCost
	)
	{
		m_playerMeshCount = playerMeshCount;
		m_playerAttackCost = playerAttackCost;
	}


	// 内部実装
private:

};
