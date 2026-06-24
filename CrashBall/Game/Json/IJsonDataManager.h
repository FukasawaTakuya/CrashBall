#pragma once
#include "nlohmann/json.hpp"

using namespace nlohmann;

/**
 * @brief Jsonデータ管理クラスのインターフェース
 */
class  IJsonDataManager {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:



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

	virtual json* GetJsonData(const std::string& key) = 0;

	// 内部実装
private:

};
