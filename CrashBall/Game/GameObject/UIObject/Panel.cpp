/*****************************************************************//**
 * \file   Panel.h
 * \brief  UIをまとめるパネルオブジェクト
 *
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/


#include "pch.h"
#include "Panel.h"

/**
 * \brief コンストラクタ
 * 
 */
Panel::Panel()
{
	AddComponent<RectTransform>();
}

/**
 * \brief デストラクタ
 * 
 */
Panel::~Panel()
{
}
