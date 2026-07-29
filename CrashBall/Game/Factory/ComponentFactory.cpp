#include "pch.h"
#include "ComponentFactory.h"
#include "Game/Component/Default/Physics/RigidBody.h"

namespace
{
	// コンポネント生成関数テーブルの取得
	std::unordered_map<std::string, ComponentFactory::CreataFunc>& GetTable()
	{
		static std::unordered_map<std::string, ComponentFactory::CreataFunc> m_createCompTable;
		return m_createCompTable;
	}
}

/**
 * \brief Jsonからコンポーネントを生成
 * 
 * \param compName コンポーネント名
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 * \return コンポーネント
 */
std::unique_ptr<Component> ComponentFactory::CreataFromJson(
	const std::string& compName,
	IGameObject* gameObject)
{
	return std::move(GetTable()[compName](gameObject));
}

/**
 * \brief コンポーネント生成関数の登録
 * 
 * \param compName コンポーネント名
 * \param func コンポーネント生成関数
 */
void ComponentFactory::RegistComponentFunc(
	const std::string& compName, 
	CreataFunc func)
{
	GetTable().emplace(compName, func);
}
