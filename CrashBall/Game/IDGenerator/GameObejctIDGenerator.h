/*****************************************************************//**
 * \file   GameObejctIDGenerator.h
 * \brief  GameObjectのID加算
 * 
 * \author 深沢拓矢
 * \date   September 2026
 *********************************************************************/

#pragma once
#include <algorithm>

namespace GameObejctIDGenerator
{
	inline int g_gameObjectID = 0;

	// 一番大きいIDか調べる 
	inline void CheckMaxID(int id)
	{
		g_gameObjectID =
			std::max(id, g_gameObjectID);
	}

	// IDの取得 
	inline int GetID()
	{
		return ++g_gameObjectID;
	}
}
