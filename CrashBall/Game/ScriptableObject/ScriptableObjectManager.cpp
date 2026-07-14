/*****************************************************************//**
 * \file   ScriptableObjectManager.cpp
 * \brief  ScriptableObject管理
 *
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#include "pch.h"
#include "ScriptableObjectManager.h"

/**
 * \brief コンストラクタ
 * 
 */
ScriptableObjectManager::ScriptableObjectManager()
{
}


/**
 * \brief デストラクタ
 * 
 */
ScriptableObjectManager::~ScriptableObjectManager()
{
}

/**
 * \brief ScriptableObjectの登録
 * 
 * \param key キー
 * \param object 登録するオブジェクト
 */
void ScriptableObjectManager::RegisterObject(
	const std::string& key,
	std::unique_ptr<ScriptableObject> object)
{
	m_scriptableObjectList.emplace(key, std::move(object));
}

/**
 * \brief パラメータの保存
 * 
 */
void ScriptableObjectManager::SaveParam()
{
	for (auto& object : m_scriptableObjectList)
	{
		object.second->SaveParam();
	}
}

/**
 * \brief パラメータの再読み込み
 * 
 */
void ScriptableObjectManager::ReloadParam()
{
	for (auto& object : m_scriptableObjectList)
	{
		object.second->ReloadParam();
	}
}

/**
 * \brief ScriptableObjectの取得
 * 
 * \param key キー
 * \return ScriptableObjectのポインタ
 */
const ScriptableObject* ScriptableObjectManager::GetScriptableObject(const std::string& key)
{
	if (m_scriptableObjectList.find(key) != m_scriptableObjectList.end())
	{
		return m_scriptableObjectList[key].get();
	}
	else return nullptr;
}
