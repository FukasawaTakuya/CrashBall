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

	virtual std::unordered_map<std::string, ordered_json>& GetGameObjectData() = 0;

	// ゲームオブジェクトデータの保存
	virtual void SaveGameObjectData() = 0;

	// ゲームオブジェクトデータの削除
	virtual void DeleteGameObjectData(const std::string& objName) = 0;

	// ゲームオブジェクトデータの追加
	virtual void AddGameObjectData(const std::string& objName) = 0;

	// 内部実装
private:

};
