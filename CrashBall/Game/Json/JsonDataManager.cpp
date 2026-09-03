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
 * \brief データの読み込み
 * 
 * \param key キー
 * \param fileName ファイル名
 */
void JsonDataManager::LoadFile(
	const std::string& key,
	const char* fileName)
{
	std::ifstream ifs(fileName);

	if (!ifs.is_open())
	{
		return;
	}

	json data;

	ifs >> data;

	m_jsonData.emplace(key, data);
	m_files.emplace(key, fileName);
}

/**
 * \brief データの再読み込み
 * 
 */
void JsonDataManager::ReloadFile()
{
	for (auto& j : m_jsonData)
	{
		std::ifstream ifs(m_files[j.first]);
		ifs >> j.second;
	}
}

/**
 * \brief データの書き込み
 * 
 */
void JsonDataManager::SaveFile()
{
	for (auto& j : m_jsonData)
	{
		std::ofstream ofs("Resources/Data/" + j.first + ".json");
		ofs << j.second.dump(4);
	}
}

/**
 * \brief ゲームオブジェクトの読み込み
 * 
 * \param filepath ファイルパス
 */
void JsonDataManager::LoadGameObject(const std::string& filepath)
{
	std::ifstream ifs(filepath);

	if (!ifs.is_open())
	{
		return;
	}

	ordered_json data;

	ifs >> data;

	m_gameObjectData.emplace(data["name"], data);
	m_gameObjectFiles.emplace(data["name"], filepath);
}

/**
 * \brief プレイマネージャーの読み込み
 * 
 * \param filepath ファイルパス
 */
void JsonDataManager::LoadPlayManager(const std::string& filepath)
{
	std::ifstream ifs(filepath);

	if (!ifs.is_open())
	{
		return;
	}

	json data;

	ifs >> data;

	m_playManagerData = data;
	m_playManagerFile = filepath;
}

/**
 * \brief ゲームオブジェクトの保存
 * 
 */
void JsonDataManager::SaveGameObject()
{
	for (auto& file : m_gameObjectFiles)
	{
		std::ofstream ofs(file.second);
		ofs << m_gameObjectData[file.first].dump(4);
	}
}

/**
 * \brief Jsonデータの取得
 * 
 * \param key キー
 * \return Jsonデータ
 */
ordered_json* JsonDataManager::GetJsonData(const std::string& key)
{
	auto it = m_jsonData.find(key);

	if (it != m_jsonData.end())
	{
		return &it->second;
	}
	// 見つからなければ新たにデータを作る
	else
	{
		m_jsonData.emplace(key, json::object());
		m_files.emplace(key, "Resources/Data/" + key + ".json");

		std::ofstream ofs("Resources/Data/" + key + ".json");
		ofs << m_jsonData[key].dump(2);

		return &m_jsonData[key];
	}
}
