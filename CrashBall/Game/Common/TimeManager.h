/*****************************************************************//**
 * \file   TimeManager.h
 * \brief  時間管理クラス 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "Game/ServiceLocator/ITimeService.h"

/**
 * @brief 時間管理クラス
 */
class  TimeManager : public ITimeService{

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	float m_elapsedTime = 0.0f;

	float m_timeScale = 1.0f;


	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	TimeManager() = default;

	// デストラクタ
	~TimeManager() = default;

	// 操作
public:

	// 取得/設定
public:

	float GetElapsedTime() const override
	{
		return m_elapsedTime * m_timeScale;
	}

	float GetUnscaleElapsedTime() const override
	{
		return m_elapsedTime;
	}

	void SetTimeScale(float timeScale) override
	{
		m_timeScale = timeScale;
	}

	void SetElapsedTime(float elapsedTime)
	{
		m_elapsedTime = elapsedTime;
	}

	// 内部実装
private:

};
