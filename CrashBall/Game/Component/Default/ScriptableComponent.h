#pragma once

#include "Game/Component/Default/Component.h"
#include <variant>

// 要素の型
enum class ValueType
{
	Float,
	Vector2,
	Vector3,
	Color,
	String,
};

/**
 * @brief 
 */
class  ScriptableComponent : public Component {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	using Value = std::variant<
		float,
		DirectX::SimpleMath::Vector2,
		DirectX::SimpleMath::Vector3,
		DirectX::XMVECTORF32,
		std::string
		>;

	using Element = std::pair<ValueType, Value>;

	std::unordered_map<std::string, Element> m_values;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	ScriptableComponent(IGameObject* gameObject);

	// デストラクタ
	~ScriptableComponent();

	// 操作
public:

	// 要素の追加
	void AddValue(
		const std::string& key,
		ValueType type,
		const Value& value
	);

	// 取得/設定
public:

	// 要素の取得
	Value GetValue(const std::string& key)
	{
		if (m_values.find(key) != m_values.end())
		{
			return m_values[key].second;
		}
		else Value();
	}

	// 内部実装
private:

	const std::unordered_map<std::string, Element>& GetValueList() const
	{
		return m_values;
	}

private:

	friend void to_json(json& j, const ScriptableComponent::Value& Value);
	friend void to_json(json& j, const ScriptableComponent::Element& element);
	friend void to_json(json& j, const ScriptableComponent& scritableComponent);

};
