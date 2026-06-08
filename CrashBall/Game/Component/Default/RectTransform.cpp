/*****************************************************************//**
 * \file   RectTransform.h
 * \brief  2Dのトランスフォームコンポーネント
 *
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#include "pch.h"
#include "RectTransform.h"

RectTransform::RectTransform(IGameObject* gameObject)
	: Component(gameObject)
{
}

RectTransform::~RectTransform()
{
}
