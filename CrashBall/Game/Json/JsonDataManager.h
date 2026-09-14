/*****************************************************************//**
 * \file   JsonDataManager.h
 * \brief  Json管理クラス
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/
#pragma once

#include "Game/Json/IJsonDataManager.h"

/**
 * \brief Json管理クラス 
 */
class  JsonDataManager : public IJsonDataManager {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	std::string m_saveFilePath;

	std::unordered_map<std::string, std::string> m_gameObjectFiles;	// ファイル名
	std::unordered_map<std::string, ordered_json> m_gameObjectData;	// Jsonデータ

	ordered_json m_playManagerData;
	std::string m_playManagerFile;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	JsonDataManager();

	// デストラクタ
	~JsonDataManager();

	// 操作
public:

	// ゲームオブジェクトの読み込み
	void LoadGameObject(const std::string& filepath);

	// プレイマネージャーの読み込み
	void LoadPlayManager(const std::string& filepath);

	// ゲームオブジェクトの保存
	void SaveGameObjectData() override;

	// ゲームオブジェクトの削除
	void DeleteGameObjectData(const std::string& objName) override;

	// ゲームオブジェクトの追加
	void AddGameObjectData(const std::string& objName) override;

	// 取得/設定
public:

	// ゲームオブジェクトデータの取得
	ordered_json* GetGameObjectData(const std::string& objName)
	{
		auto it = m_gameObjectData.find(objName);
		if (it != m_gameObjectData.end())
		{
			return &(it->second);
		}
		else
		{
			return nullptr;
		}
	}

	// ゲームオブジェクトデータの取得
	std::unordered_map<std::string, ordered_json>& GetGameObjectData() override
	{
		return m_gameObjectData;
	}

	// 保存ファイルパスの設定
	void SetSaveFilePath(const std::string& filePath)
	{
		m_saveFilePath = filePath;
	}

	// 内部実装
private:

};
