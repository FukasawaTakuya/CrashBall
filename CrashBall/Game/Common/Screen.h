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
	// フルスクリーン
	static constexpr float FULL_WIDTH = 1920.0f;
	static constexpr float FULL_HEIGHT = 1080.0f;

	static constexpr float WIDTH = 1280.0f;
	static constexpr float HEIGHT = 720.0f;
	static constexpr float CENTER_X = WIDTH / 2.0f;
	static constexpr float CENTER_Y = HEIGHT / 2.0f;

	void CalcScreenRate(bool isFullScreen);

	float GetScreenRate();
}
