#include "pch.h"
#include "Game/Component/Default/Component.h"
#include "ComponentFactory.h"

namespace
{

	// コンポネント生成関数テーブルの取得
	std::unordered_map<std::string, ComponentFactory::CreataFunc>& GetTable()
	{
		static std::unordered_map<std::string, ComponentFactory::CreataFunc> m_createCompTable;
		return m_createCompTable;
	}

	std::vector<std::string>& GetCompNameList()
	{
		static std::vector<std::string> s_compNameList;
		return s_compNameList;
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
	GetCompNameList().push_back(compName);
}

const std::vector<std::string>& ComponentFactory::GetCompNames()
{
	return GetCompNameList();
}
