#include "pch.h"
#include "ScriptableComponent.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 * \param gameObject
 */
ScriptableComponent::ScriptableComponent(IGameObject* gameObject)
{
}

/**
 * \brief デストラクタ
 * 
 */
ScriptableComponent::~ScriptableComponent()
{
}

/**
 * \brief 要素の追加
 *
 * \param key キー
 * \param type 型情報(どの型として扱うか)
 * \param value 数値
 */
void ScriptableComponent::AddValue(
	const std::string& key, 
	ValueType type, 
	const Value& value)
{
	m_values.emplace(
		key,
		std::pair(type, value)
	);
}