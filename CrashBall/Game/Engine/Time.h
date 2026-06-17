/*****************************************************************//**
 * \file   Time.h
 * \brief  時間取得するためのグローバル関数一覧
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once

#include "Game/ServiceLocator/ServiceLocator.h"
#include "Game/ServiceLocator/ITimeService.h"

namespace Time
{
	// スケーリング有りの経過時間の取得
	inline float GetElapsedTime()
	{
		// 時間管理システム
		static ITimeService* time = ServiceLocator::Get<ITimeService>();
		// 時間管理システムが存在すれば数値を返す
		if (time != nullptr)
		{
			return time->GetElapsedTime();
		}
		// なければ0.0f
		else return 0.0f;
	}

	// スケーリング無しの経過時間の取得
	inline float GetUnscaleElapsedTime()
	{
		// 時間管理システム
		static ITimeService* time = ServiceLocator::Get<ITimeService>();
		// 時間管理システムが存在すれば数値を返す
		if (time != nullptr)
		{
			return time->GetUnscaleElapsedTime();
		}
		// なければ0.0f
		else return 0.0f;
	}

	// タイムスケールの設定
	inline void SetTimeScale(float timeScale)
	{
		// 時間管理システム
		static ITimeService* time = ServiceLocator::Get<ITimeService>();
		// 時間管理システムが存在すれば数値を設定する
		if (time != nullptr)
		{
			return time->SetTimeScale(timeScale);
		}
	}
}
