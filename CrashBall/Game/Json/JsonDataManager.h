/*****************************************************************//**
 * \file   JsonDataManager.h
 * \brief  Json管理クラス
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/
#pragma once

/**
 * \brief Json管理クラス
 */
class  JsonDataManager {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	std::unordered_map<std::string, std::wstring> m_files;	// ファイル名
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
	void LoadFile(const std::string& key, const wchar_t* fileNmae);

	// データの再読み込み
	void ReloadFile();

	// データの書き込み
	void SaveFile();

	// 取得/設定
public:

	// Jsonデータの取得
	json* GetJson(const std::string& key);

	// 内部実装
private:

};
