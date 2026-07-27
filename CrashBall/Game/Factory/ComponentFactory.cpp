#include "pch.h"
#include "ComponentFactory.h"

namespace
{
	// コンポネント生成関数テーブル
	std::unordered_map<std::string, ComponentFactory::CreataFunc> m_createComp;
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
	m_createComp.emplace(compName, func);
}
