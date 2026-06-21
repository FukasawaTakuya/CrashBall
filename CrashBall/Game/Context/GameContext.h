/*****************************************************************//**
 * \file   GameContext.h
 * \brief  ゲームプレイ用のコンテキスト
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once

#include "Game/SoundPlayer/ISoundPlayer.h"

/**
 * @brief ゲームプレイ用のコンテキスト
 */
struct  GameContext {
	ISoundPlayer* soundManager = nullptr;	// サウンド再生
};
