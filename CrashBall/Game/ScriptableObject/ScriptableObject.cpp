/*****************************************************************//**
 * \file   ScriptableObject.cpp
 * \brief  
 * 
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#include "pch.h"
#include "ScriptableObject.h"

ScriptableObject::ScriptableObject(json* data)
	: GameObject(data)
{
	m_scriptable = AddComponent<ScriptableComponent>((*data)["scriptable"]);
}
