/*****************************************************************//**
 * \file   GameManager.h
 * \brief  ゲームマネージャー
 * 
 * \author 深沢拓矢
 * \date   September 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"
#include "Game/Component/Enemy/EnemyController.h"
#include "Game/Component/GameTimer.h"
#include "Game/Component/ResultPanel.h"
#include "Game/Component/ChangeSceneScreen/ChangeSceneScreen.h"

/**
 * @brief ゲームマネージャー
 */
class  GameManager : public Component {

	// メンバ変数の宣言 -------------------------------------------------
private:

	const EnemyController*	m_pEnemyController	= nullptr;	// 敵体力取得用
	GameTimer*				m_pGameTimer		= nullptr;	// ゲームタイマー
	ChangeSceneScreen*		m_changeSceneScreen	= nullptr;	// シーン遷移スクリーン

	// プロパティの設定
	BeginProperty()
		AddProperty(m_pEnemyController,  PropertyType::Component)
		AddProperty(m_pGameTimer,		 PropertyType::Component)
		AddProperty(m_changeSceneScreen, PropertyType::Component)
	EndProperty()

	// コンポーネント名の設定
	SetCompName("GameManager")

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	GameManager(IGameObject* gameObject);

	// デストラクタ
	~GameManager() = default;

	// 操作
public:

	// 開始処理
	void Start(const GameContext& gameContext) override;

	// 更新
	void Update(const GameContext& gameContext) override;

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