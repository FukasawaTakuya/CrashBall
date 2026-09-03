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

	friend class ObjectInspectorGui;

	// データメンバの宣言 -----------------------------------------------
private:

	using Value = std::variant<
		float,
		DirectX::SimpleMath::Vector2,
		DirectX::SimpleMath::Vector3,
		DirectX::SimpleMath::Color,
		std::string
		>;

	using Element = std::pair<ValueType, Value>;

	std::unordered_map<std::string, Element> m_values;


	// プロパティの設定
	BeginProperty()
	EndProperty()

	// コンポーネント名の設定
	SetCompName("Scriptable")


	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// デフォルトコンストラクタ
	ScriptableComponent() = default;

	// コンストラクタ
	ScriptableComponent(IGameObject* gameObject);

	//// コピーコンストラクタ
	//ScriptableComponent(
	//	IGameObject* gameObject,
	//	const ScriptableComponent& other);

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
	template<typename T>
	T GetValue(const std::string& key) const
	{
		auto it = m_values.find(key);

		if (it != m_values.end())
		{
			return std::get<T>(it->second.second);
		}
		else T;
	}

	// 内部実装
private:

	std::unordered_map<std::string, Element>& GetValueList()
	{
		return m_values;
	}

	const std::unordered_map<std::string, Element>& GetValueList() const
	{
		return m_values;
	}

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

	// JsonConverter
private:

	friend void to_json(nlohmann::json& j, const ScriptableComponent::Element& element);
	friend void to_json(nlohmann::json& j, const ScriptableComponent& scritableComponent);

	friend void from_json(const nlohmann::json& j, ScriptableComponent::Element& element);
	friend void from_json(const nlohmann::json& j, ScriptableComponent& scriptable);

	// 演算子オーバーロード
public:

	void operator=(const ScriptableComponent& other)
	{
		m_values.clear();
		m_values = other.m_values;
	}
};
