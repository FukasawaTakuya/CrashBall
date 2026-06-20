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


/**
 * @brief 攻撃ゲージ操作コンポーネント
 */
class  AttackGaugeController : public Component {

	// クラス定数の宣言 -------------------------------------------------
private:

	// 攻撃ゲージの描画位置
	static constexpr DirectX::SimpleMath::Vector2
		GAUGE_POSITION = DirectX::SimpleMath::Vector2(Screen::CENTER_X, Screen::CENTER_Y + 150.f);

	// 攻撃力表示テキストの描画位置
	static constexpr DirectX::SimpleMath::Vector2
		TEXT_POSITION = DirectX::SimpleMath::Vector2(Screen::CENTER_X, Screen::CENTER_Y + 190.f);
	
	static constexpr float GAUGE_SCALE			= 0.4f;		// ゲージのスケール
	static constexpr float GAUGE_SLIDE_SPEED	= 5.0f;		// ゲージのスライド速度
	static constexpr float GAUGE_LAYER_DEPTH	= 0.1f;		// ゲージの描画順
	static constexpr float TEXT_LAYER_DEPTH		= 0.2f;		// テキストの描画順
	static constexpr float TEXT_FONTSCALE		= 0.35f;	// テキストのフォントスケール

	// データメンバの宣言 -----------------------------------------------
private:

	IGameObject* m_pAttackGauge		  = nullptr;	// 攻撃ゲージ
	IGameObject* m_pAttackGaugeTrack  = nullptr;	// 攻撃ゲージの土台
	IGameObject* m_pAttackPowerText	  = nullptr;	// 攻撃力表示テキスト

	SpriteRenderer* m_gaugeRenderer				= nullptr;	// ゲージの描画コンポーネントのキャッシュ
	TextRenderer*	m_attackPowerTextRenderer	= nullptr;	// 攻撃力表示テキスト描画コンポーネントのキャッシュ

	int m_playerMeshCount	= 0;	// プレイヤーの面の数
	int m_playerAttackCost	= 0;	// プレイヤーの攻撃コスト
	int m_playerAttackPower = 0;	// プレイヤーの攻撃力

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	AttackGaugeController(
		IGameObject* gameObejct,
		IGameObject* pAttackGauge,
		IGameObject* pAttackGaugeTrack,
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

};
