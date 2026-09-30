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
#include "Game/Component/Stage/StageController.h"


/**
 * @brief 床メッシュゲージ操作コンポーネント
 */
class  FloorMeshGaugeController : public Component {

	// メンバ変数の宣言 -----------------------------------------------
private:

	// 管理ゲームオブジェクト
	IGameObject* m_pPalyerMeshGauge		= nullptr;	// プレイヤーが塗った面のゲージ
	IGameObject* m_pEnemyMeshGauge		= nullptr;	// 敵が塗った面のゲージ
	IGameObject* m_pPlayerMeshNumText	= nullptr;	// プレイヤーのメッシュ数表示
	IGameObject* m_pEnemyMeshNumText	= nullptr;	// 敵のメッシュ数表示

	const StageController* m_pStageController = nullptr;	// 面の数取得用

	// ゲージのコンポーネントのキャッシュ
	SliderController* m_playerGaugeController	= nullptr;
	SliderController* m_enemyGaugeController	= nullptr;

	// テキストのコンポーネントのキャッシュ
	TextRenderer* m_playerTextRenderer = nullptr;
	TextRenderer* m_enemyTextRenderer  = nullptr;

	// プロパティの設定
	BeginProperty()
		AddProperty(m_pPalyerMeshGauge	, PropertyType::GameObject)
		AddProperty(m_pEnemyMeshGauge	, PropertyType::GameObject)
		AddProperty(m_pPlayerMeshNumText, PropertyType::GameObject)
		AddProperty(m_pEnemyMeshNumText	, PropertyType::GameObject)
		AddProperty(m_pStageController	, PropertyType::Component)
	EndProperty()

	// コンポーネント名の設定
	SetCompName("FloorMeshGaugeController")


	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	FloorMeshGaugeController(IGameObject* gameObject);

	// デストラクタ
	~FloorMeshGaugeController() = default;

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