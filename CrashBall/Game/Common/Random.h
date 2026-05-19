/*****************************************************************//**
 * \file   Random.h
 * \brief  乱数生成クラス 
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/
#pragma once

#include <random>

/**
 * @brief 乱数生成クラス
 */
class  Random {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	// 乱数生成エンジン
	std::mt19937 m_randomEngin;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
private:

	// コンストラクタ
	Random()
		: m_randomEngin(std::random_device{}()) {};

	// 複数生成の禁止
	Random(Random&) = delete;
	Random& operator=(const Random&) = delete;

	// デストラクタ
	~Random() = default;

	// 操作
public:

	// 取得/設定
public:

	// 乱数の生成(int型)
	static int Range(int min, int max) {
		// インスタンスの取得
		auto& instance = GetInstance();

		std::uniform_int_distribution<int> dist(min, max);
		return dist(instance.m_randomEngin);
	}

	// 乱数の生成(float型)
	static float Range(float min, float max) {
		// インスタンスの取得
		auto& instance = GetInstance();

		std::uniform_real_distribution<float> dist(min, max);
		return dist(instance.m_randomEngin);
	}

	// 内部実装
private:

	// インスタンスの取得
	static Random& GetInstance()
	{
		static Random instance;
		return instance;
	}

};
