/*****************************************************************//**
 * \file   DebugCameraController.cpp
 * \brief  デバッグ用カメラ操作コンポーネント
 *
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#include "pch.h"
#include "DebugCameraController.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 *  
 */
DebugCameraController::DebugCameraController(IGameObject* gameObject)
	: TargetCameraController(
		gameObject,
		SimpleMath::Vector3(0.0f, 10.0f, 10.0f))
{
}

/**
 * \brief デストラクタ
 * 
 */
DebugCameraController::~DebugCameraController()
{
}

void DebugCameraController::Update()
{
}
