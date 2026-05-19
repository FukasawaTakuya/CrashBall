/*****************************************************************//**
 * \file   Time.h
 * \brief  時間取得するためのグローバルAPI 
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
		return ServiceLocator::Get<ITimeService>()->GetElapsedTime();
	}

	// スケーリング無しの経過時間の取得
	inline float GetUnscaleElapsedTime()
	{
		return ServiceLocator::Get<ITimeService>()->GetUnscaleElapsedTime();
	}

	// タイムスケールの設定
	inline void SetTimeScale(float timeScale)
	{
		ServiceLocator::Get<ITimeService>()->SetTimeScale(timeScale);
	}
}
