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
#include "Game/Component/Default/UI/SliderController.h"
#include "Game/Component/Enemy/EnemyController.h"


/**
 * @brief 敵HPゲージ操作コンポーネント
 */
class  EnemyHpGaugeController : public Component {

	// メンバ変数の宣言 -----------------------------------------------
private:

	IGameObject* m_pEnemyHpGauge		= nullptr;	// 敵のHPゲージ
	IGameObject* m_pEnemyHpGaugeTrack	= nullptr;	// 敵のHPゲージの土台
	IGameObject* m_pEnemyHpText			= nullptr;	// 敵のHPの表示テキスト

	const EnemyController* m_pEnemyController = nullptr;	// 敵HP取得用

	SliderController* m_enemyHpGaugeController = nullptr;	// HPゲージの操作コンポーネント
	TextRenderer* m_enemyHpTextRenderer		   = nullptr;	// テキストの描画コンポーネント

	// プロパティの設定
	BeginProperty()
		AddProperty(m_pEnemyHpGauge, PropertyType::GameObject)
		AddProperty(m_pEnemyHpGaugeTrack, PropertyType::GameObject)
		AddProperty(m_pEnemyHpText, PropertyType::GameObject)
		AddProperty(m_pEnemyController, PropertyType::Component)
	EndProperty()

	// コンポーネント名の設定
	SetCompName("EnemyHpGaugeController")


	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	EnemyHpGaugeController(IGameObject* gameObject);

	// デストラクタ
	~EnemyHpGaugeController() = default;

	// 操作
public:

	// アタッチ時の処理
	void Awake() override;

	// 開始処理
	void Start(const GameContext& gameContext) override;

	// 更新
	void Update(const GameContext& gameContext) override;

	// 取得/設定
public:

	// 内部実装
private:
	// プロパティの取得
	virtual const std::vector<PropertyInfo>& GetProperties() const override
	{
		return m_properties;
	}

	// コンポーネント名の取得
	virtual std::string GetCompName() const override
	{
		return m_compName;
	}
};
