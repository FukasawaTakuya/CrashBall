/*****************************************************************//**
 * \file   JsonDataManager.h
 * \brief  Json管理クラス
 *
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#include "pch.h"
#include "JsonDataManager.h"

#include <fstream>
#include "Game/Scene/SceneManager.h"

#include "Game/IDGenerator/GameObejctIDGenerator.h"

/**
 * \brief コンストラクタ
 * 
 */
JsonDataManager::JsonDataManager()
{
}

/**
 * \brief デストラクタ
 * 
 */
JsonDataManager::~JsonDataManager()
{
}


/**
 * \brief ゲームオブジェクトの読み込み
 * 
 * \param filepath ファイルパス
 */
void JsonDataManager::LoadGameObjectData(const std::string& filepath)
{
	std::ifstream ifs(filepath);

	if (!ifs.is_open())
	{
		return;
	}

	ordered_json data;

	ifs >> data;

	m_gameObjectData.emplace(data["name"], data);

	// 最大IDか調べる
	GameObejctIDGenerator::CheckMaxID(data["id"].get<int>());
}

/**
 * \brief ゲームオブジェクトの保存
 * 
 */
void JsonDataManager::SaveGameObjectData()
{
	for (auto it = m_gameObjectData.begin(); it != m_gameObjectData.end();)
	{
		std::string objName = it->second["name"].get<std::string>();

		// オブジェクト名が変更されていたら
		if (it->first != objName)
		{
			// 抽出
			auto node = m_gameObjectData.extract(it++);
			// キーを変更
			node.key() = objName;

			// 挿入し直す
			m_gameObjectData.insert(std::move(node));

			continue;
		}

		std::ofstream ofs(m_saveFilePath + objName + ".json");
		ofs << it->second.dump(4);

		it++;
	}
}

/**
 * \brief ゲームオブジェクトデータの削除
 * 
 * \param objName オブジェクト名
 */
void JsonDataManager::DeleteGameObjectData(const std::string& objName)
{

	// ゲームオブジェクトデータの削除
	{
		auto it = m_gameObjectData.find(objName);
		if (it != m_gameObjectData.end())
		{
			m_gameObjectData.erase(it);
		}
	}
}

/**
 * \brief ゲームオブジェクトの追加
 * 
 * \param objName オブジェクト名
 */
ordered_json* JsonDataManager::AddGameObjectData(const std::string& objName)
{
	m_gameObjectData.emplace(objName, ordered_json());

	auto& it = m_gameObjectData[objName];

	return &it;
}
