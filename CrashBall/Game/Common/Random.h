// 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include <random>

// クラスの前方宣言 ===================================================



// クラスの定義 ===============================================================
/**
 * @brief 基底オブジェクト
 */
class  Random {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	// 乱数生成エンジン
	std::mt19937 m_mt;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
private:

	// コンストラクタ
	Random()
		: m_mt(std::random_device{}()) {};
	// コピーコンストラクタと代入演算子を削除
	Random(Random&) = delete;
	Random& operator=(const Random&) = delete;

	// デストラクタ
	~Random() = default;

	// 操作
public:
	// インスタンスの取得
	static Random& Instance() {
		static Random instance;
		return instance;
	}

	// 取得/設定
public:

	// 乱数の生成(int型)
	int Range(int min, int max) {
		std::uniform_int_distribution<int> dist(min, max);
		return dist(m_mt);
	}

	// 乱数の生成(float型)
	float Range(float min, float max) {
		std::uniform_real_distribution<float> dist(min, max);
		return dist(m_mt);
	}

	// 内部実装
private:

};
