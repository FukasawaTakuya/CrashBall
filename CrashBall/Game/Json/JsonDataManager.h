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

	std::unordered_map<std::string, std::string> m_files;	// ファイル名
	std::unordered_map<std::string, ordered_json> m_jsonData;		// Jsonデータ

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

	// データの読み込み
	void LoadFile(const std::string& key, const char* fileNmae);

	// データの再読み込み
	void ReloadFile() override;

	// データの書き込み
	void SaveFile() override;

	// ゲームオブジェクトの読み込み
	void LoadGameObject(const std::string& filepath);

	// プレイマネージャーの読み込み
	void LoadPlayManager(const std::string& filepath);

	// ゲームオブジェクトの保存
	void SaveGameObject() override;

	// 取得/設定
public:

	// Jsonデータの取得
	ordered_json* GetJsonData(const std::string& key) override;

	std::unordered_map<std::string, ordered_json>& GetGameObjectData() override
	{
		return m_gameObjectData;
	}

	ordered_json GetPlayManagerData()
	{
		return m_playManagerData;
	}

	// 内部実装
private:

};
