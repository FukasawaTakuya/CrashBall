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
	static int s_gameObjectID = 0;

	// 一番大きいIDか調べる 
	inline void CheckMaxID(int id)
	{
		s_gameObjectID =
			std::max(id, s_gameObjectID);
	}

	// IDの加算 
	inline void GeneratID()
	{
		s_gameObjectID++;
	}
}
