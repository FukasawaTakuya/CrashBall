/*****************************************************************//**
 * \file   DebugCamera.cpp
 * \brief  デバッグカメラ
 *
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/


#include "pch.h"
#include "DebugCamera.h"

/**
 * \brief コンストラクタ
 * 
 */
DebugCamera::DebugCamera()
{
	AddComponent<Transform>();
	AddComponent<Camera>();
	AddComponent<DebugCameraController>();
}

/**
 * \brief デストラクタ
 * 
 */
DebugCamera::~DebugCamera()
{
}