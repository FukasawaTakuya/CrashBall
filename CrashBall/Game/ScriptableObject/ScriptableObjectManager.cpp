/*****************************************************************//**
 * \file   ScriptableObjectManager.cpp
 * \brief  ScriptableObject管理
 *
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#include "pch.h"
#include "ScriptableObjectManager.h"

#include <fstream>
#include "Game/Factory/GameObjectFactory.h"

/**
 * \brief コンストラクタ
 * 
 */
ScriptableObjectManager::ScriptableObjectManager()
	: m_jsonManager(std::make_unique<JsonDataManager>())
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
 * \brief ScriptableObjectのロード
 * 
 */
void ScriptableObjectManager::LoadScriptableObject()
{
	std::string filepath = "Resources/Data/ScriptableObjects";

	if(m_jsonManager.get() == nullptr) return;

	// jsonデータの読み込み
	for (auto& entity : std::filesystem::recursive_directory_iterator(filepath))
	{
		std::string s = entity.path().string();
		m_jsonManager->LoadGameObject(s);
	}

	// オブジェクトの生成
	for (auto& data : m_jsonManager->GetGameObjectData())
	{
		// オブジェクトの生成
		auto obj = GameObjectFactory::CreateScriptableObjectFromJson(data.second);
		m_scriptableObjectList.emplace(obj->Get()->GetScirptableTypeid(), std::move(obj));
	}
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
	//m_scriptableObjectList.emplace(key, std::move(object));
}

/**
 * \brief パラメータの保存
 * 
 */
void ScriptableObjectManager::SaveData()
{
	for (auto& object : m_scriptableObjectList)
	{
		object.second->SaveData();
	}

	m_jsonManager->SaveGameObjectData();
}
