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
