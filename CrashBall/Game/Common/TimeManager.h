/*****************************************************************//**
 * \file   TimeManager.h
 * \brief  時間管理クラスに関するヘッダーファイル
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

// 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================

// クラスの前方宣言 ===================================================



// クラスの定義 ===============================================================
/**
 * @brief 基底オブジェクト
 */
class  TimeManager {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	float m_elapsedTime = 0.0f;

	float m_timeScale = 1.0f;


	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
private:

	// コンストラクタ
	TimeManager() = default;
	TimeManager(const TimeManager&) = delete;
	TimeManager& operator=(const TimeManager&) = delete;

	// デストラクタ
	~TimeManager() = default;

	// 操作
public:

	// 取得/設定
public:

	static TimeManager& Instance() {
		static TimeManager instance;
		return instance;
	}

	float GetElapsedTime() const
	{
		return m_elapsedTime * m_timeScale;
	}

	float GetUnscaleElapsedTime() const
	{
		return m_elapsedTime;
	}

	void SetElapsedTime(float elapsedTime)
	{
		m_elapsedTime = elapsedTime;
	}

	void SetTimeScale(float timeScale)
	{
		m_timeScale = timeScale;
	}

	// 内部実装
private:

};
