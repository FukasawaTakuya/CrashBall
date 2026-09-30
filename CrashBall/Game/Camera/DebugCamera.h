/*****************************************************************//**
 * \file   DebugCamera.h
 * \brief  デバッグカメラ
 * 
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#pragma once

#include "Game/GameObject/GameObject.h"

#include "Game/Component/Camera/DebugCameraController.h"

/**
 * \brief デバッグカメラ
 */
class  DebugCamera : public GameObject
{

	// メンバ変数の宣言 -----------------------------------------------
private:

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	DebugCamera();

	// デストラクタ
	~DebugCamera();

	// 操作
public:

	// 取得/設定
public:

	// 内部実装
private:

};
