/*****************************************************************//**
 * \file   TimeManager.h
 * \brief  時間管理クラスに関するヘッダーファイル
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "Game/Interface/ITimeManager.h"

/**
 * @brief 時間管理クラス
 */
class  TimeManager : public ITimeManager{

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

	float GetElapsedTime() const override
	{
		return m_elapsedTime * m_timeScale;
	}

	float GetUnscaleElapsedTime() const override
	{
		return m_elapsedTime;
	}

	void SetElapsedTime(float elapsedTime) override
	{
		m_elapsedTime = elapsedTime;
	}

	void SetTimeScale(float timeScale) override
	{
		m_timeScale = timeScale;
	}

	// 内部実装
private:

};
