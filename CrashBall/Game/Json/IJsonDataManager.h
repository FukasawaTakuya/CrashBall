#pragma once
#include "nlohmann/json.hpp"

using namespace nlohmann;

/**
 * @brief Jsonデータ管理クラスのインターフェース
 */
class  IJsonDataManager {
	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	IJsonDataManager() = default;

	// デストラクタ
	virtual ~IJsonDataManager() = default;

	// 操作
public:

	// 取得/設定
public:

	virtual ordered_json* GetJsonData(const std::string& key) = 0;

	virtual std::unordered_map<std::string, ordered_json>& GetGameObjectData() = 0;

	virtual	ordered_json GetPlayManagerData() = 0;


	// データの再読み込み
	virtual void ReloadFile() = 0;

	// データの書き込み
	virtual void SaveFile() = 0;

	virtual void SaveGameObject() = 0;


	// 内部実装
private:

};
