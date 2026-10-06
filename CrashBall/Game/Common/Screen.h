/*****************************************************************//**
 * \file   Screen.h
 * \brief  ゲーム画面サイズ関連
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once


namespace Screen
{
	// フルスクリーンサイズ
	const float FULL_WIDTH = 1920.0f;
	const float FULL_HEIGHT = 1080.0f;

	const float WIDTH = FULL_WIDTH * 0.8f;
	const float HEIGHT = FULL_HEIGHT * 0.8f;
	const float CENTER_X = WIDTH / 2.0f;
	const float CENTER_Y = HEIGHT / 2.0f;

	void CalcScreenRate(bool isFullScreen);

	float GetScreenRate();

	float GetAccept();
}
