#pragma once

#include "Game/Component/Default/Component.h"

/**
 * @brief 
 */
class  ScriptableComponent : public Component {

private:

	// ScriptableObject個別認識用のIDの設定
	std::type_index m_scriptableTypeid;

	// プロパティの設定
	BeginProperty()
	EndProperty()

	// コンポーネント名の設定
	SetCompName("ScriptableComponent")

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// デフォルトコンストラクタ
	ScriptableComponent() = default;

	// コンストラクタ
	ScriptableComponent(IGameObject* gameObject);

	// デストラクタ
	~ScriptableComponent();

	// 操作
public:

	std::type_index GetScirptableTypeid() const
	{
		return m_scriptableTypeid;
	}

	// ScriptableObject個別認識用のIDの設定
	void SetScirptableTypeid(std::type_index type_id)
	{
		m_scriptableTypeid = type_id;
	}

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
