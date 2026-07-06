#pragma once

#include "Game/Component/Default/Component.h"
#include <variant>

// 要素の型
enum class ValueType
{
	Float,
	Vector2,
	Vector3,
	Vector4,
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

	std::unordered_map<std::string, std::pair<ValueType, Value>> m_values;

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

};
