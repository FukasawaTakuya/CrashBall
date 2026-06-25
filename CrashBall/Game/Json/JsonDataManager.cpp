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
		ofs << j.second.dump(2);
	}
}

/**
 * \brief Jsonデータの取得
 * 
 * \param key キー
 * \return Jsonデータ
 */
json* JsonDataManager::GetJsonData(const std::string& key)
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
