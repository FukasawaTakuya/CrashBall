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

/**
 * @brief 敵HPゲージ操作コンポーネント
 */
class  EnemyHpGaugeController : public Component {

	// クラス定数の宣言 -------------------------------------------------
public:

	// 敵のHPゲージの描画位置
	static constexpr DirectX::SimpleMath::Vector2 ENEMY_HP_POSITION
		= DirectX::SimpleMath::Vector2(Screen::CENTER_X, 60.0f);

	// 敵のHPの表示テキストの描画位置
	static constexpr DirectX::SimpleMath::Vector2 ENEMY_HP_TEXT_POSITION
		= DirectX::SimpleMath::Vector2(Screen::CENTER_X, 25.0f);

	static constexpr float TEXT_FONT_SCALE		= 0.5f;		// テキストのフォントスケール
	static constexpr float GAUGE_SPRITE_SCALE	= 0.8f;		// ゲージのスプライトスケール
	static constexpr float GAUGE_SLIDE_SPEED	= 5.0f;		// ゲージのスライド速度
	static constexpr float GAUGE_LAYER_DEPTH	= 0.1f;		// ゲージの描画順

	// データメンバの宣言 -----------------------------------------------
private:

	IGameObject* m_pEnemyHpGauge		= nullptr;	// 敵のHPゲージ
	IGameObject* m_pEnemyHpGaugeTrack	= nullptr;	// 敵のHPゲージの土台
	IGameObject* m_pEnemyHpText			= nullptr;	// 敵のHPの表示テキスト

	SpriteRenderer* m_enemyHpGaugeRenderer	= nullptr;	// ゲージのスプライト描画コンポーネント
	TextRenderer* m_enemyHpTextRenderer		= nullptr;	// テキストの描画コンポーネント

	int m_enemyHp = 0;		// 敵のHP
	int m_enemyMaxHp = 0;	// 敵の最大HP

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

};
