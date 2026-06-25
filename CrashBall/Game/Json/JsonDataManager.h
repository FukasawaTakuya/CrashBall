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
	std::unordered_map<std::string, json> m_jsonData;		// Jsonデータ

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
	void ReloadFile();

	// データの書き込み
	void SaveFile();

	// 取得/設定
public:

	// Jsonデータの取得
	json* GetJsonData(const std::string& key) override ;

	// 内部実装
private:

};
