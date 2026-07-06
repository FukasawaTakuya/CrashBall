/*****************************************************************//**
 * \file   Screen.cpp
 * \brief  ゲーム画面サイズ関連
 *
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#include "pch.h"
#include "Screen.h"

namespace {
	float screenRate;
}

void Screen::CalcScreenRate(bool isFullScreen)
{
	if (isFullScreen)
	{
		screenRate = 1.0f;
	}
	else
	{
		screenRate = HEIGHT / FULL_HEIGHT;
	}
}

float Screen::GetScreenRate()
{
	return screenRate;
}
