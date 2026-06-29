/*****************************************************************//**
 * \file   Panel.h
 * \brief  UIをまとめるパネルオブジェクト
 *
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/


#include "pch.h"
#include "Panel.h"

#include "Game/Json/Enum/JsonEnumSerializers.h"

/**
 * \brief コンストラクタ
 * 
 */
Panel::Panel()
{
	AddComponent<RectTransform>();
}

Panel::Panel(json* data)
	: GameObject(data)
{

	AddComponent<RectTransform>((*m_data)["rectTransform"]);
}

/**
 * \brief デストラクタ
 * 
 */
Panel::~Panel()
{
}
