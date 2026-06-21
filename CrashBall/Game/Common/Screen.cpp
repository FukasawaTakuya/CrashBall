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
		screenRate = FULL_HEIGHT / HEIGHT;
		
	}
	else
	{
		screenRate = 1.0f;
	}
}

float Screen::GetScreenRate()
{
	return screenRate;
}
