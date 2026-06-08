#include "pch.h"
#include "Screen.h"

namespace {
	float screenRate = Screen::HEIGHT / Screen::FULL_HEIGHT;
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
