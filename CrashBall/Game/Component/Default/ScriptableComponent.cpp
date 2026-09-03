#include "pch.h"
#include "ScriptableComponent.h"

using namespace DirectX;

//RegisterComponent(ScriptableComponent)


/**
 * \brief コンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 */
ScriptableComponent::ScriptableComponent(IGameObject* gameObject)
{
}

/**
 * \brief コピーコンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 * \param other コピー元
 */
//ScriptableComponent::ScriptableComponent(
//	IGameObject* gameObject, 
//	const ScriptableComponent& other)
//{
//	m_values.clear();
//	m_values = other.m_values;
//}


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