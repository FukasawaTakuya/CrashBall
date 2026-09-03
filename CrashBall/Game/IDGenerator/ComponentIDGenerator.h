/*****************************************************************//**
 * \file   ComponentIDGenerator.h
 * \brief  ComponentのID加算
 * 
 * \author 深沢拓矢
 * \date   September 2026
 *********************************************************************/

#pragma once
#include <algorithm>

namespace ComponentIDGenerator
{
	static int s_componentID = 0;

	// 一番大きいIDか調べる
	inline void CheckMaxID(int id)
	{
		s_componentID =
			std::max(id, s_componentID);
	}

	// IDの加算
	inline void GeneratID()
	{
		s_componentID++;
	}

	inline int GetID()
	{
		return s_componentID;
	}
}
