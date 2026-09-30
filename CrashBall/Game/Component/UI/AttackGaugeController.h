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
#include "Game/Component/Default/UI/SliderController.h"

#include "Game/ScriptableObject/GameColor.h"
#include "Game/Component/Player/PlayerStatusController.h"
#include "Game/Component/Stage/StageController.h"


/**
 * @brief 攻撃ゲージ操作コンポーネント
 */
class  AttackGaugeController : public Component {
	
	// メンバ変数の宣言 -----------------------------------------------
private:

	IGameObject* m_pAttackGauge		  = nullptr;	// 攻撃ゲージ
	IGameObject* m_pAttackPowerText	  = nullptr;	// 攻撃力表示テキスト

	const PlayerStatusController*	m_pPlayerStatusController	= nullptr;	// プレイヤー攻撃力表示用
	const StageController*			m_pStageController			= nullptr;	// 面の数取得用

	TextRenderer*	m_attackPowerTextRenderer	= nullptr;	// 攻撃力表示テキスト描画コンポーネントのキャッシュ
	SliderController* m_attackGaugeController	= nullptr;	// 攻撃ゲージの操作コンポーネントのキャッシュ

	const GameColor* m_gameColor = nullptr;

	// プロパティの設定
	BeginProperty()
		AddProperty(m_pAttackGauge, PropertyType::GameObject)
		AddProperty(m_pAttackPowerText, PropertyType::GameObject)
		AddProperty(m_pPlayerStatusController, PropertyType::Component)
		AddProperty(m_pStageController, PropertyType::Component)
	EndProperty()

	// コンポーネント名の設定
	SetCompName("AttackGaugeController")


	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	AttackGaugeController(IGameObject* gameObject);

	// デストラクタ
	~AttackGaugeController() = default;

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
