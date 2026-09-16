#pragma once

#include "Game/Component/Default/Component.h"

/**
 * @brief 
 */
class  TitleManager : public Component {

	// プロパティの設定
	BeginProperty()
	EndProperty()

	// コンポーネント名の設定
	SetCompName("TitleManager")

		// メンバ関数の宣言 -------------------------------------------------
		// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	TitleManager(IGameObject* gameObject);

	// デストラクタ
	~TitleManager() = default;

	// 操作
public:

	// 更新
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