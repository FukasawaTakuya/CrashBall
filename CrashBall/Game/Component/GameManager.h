#pragma once

#include "Game/Component/Default/Component.h"
#include "Enemy/EnemyController.h"
#include "GameTimer.h"
#include "ResultPanel.h"

/**
 * @brief
 */
class  GameManager : public Component {

	// メンバ変数の宣言 -------------------------------------------------
	// パラメータ
private:

	EnemyController* m_pEnemyController = nullptr;
	GameTimer* m_pGameTimer = nullptr;
	ResultPanel* m_pResultPanel = nullptr;

	// プロパティの設定
	BeginProperty()
		AddProperty(m_pEnemyController, PropertyType::Component)
		AddProperty(m_pGameTimer, PropertyType::Component)
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

	virtual void Start(const GameContext& gameContext) override;

	// 更新
	virtual void Update(const GameContext& gameContext) override;

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