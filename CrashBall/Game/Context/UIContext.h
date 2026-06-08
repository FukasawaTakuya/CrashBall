/*****************************************************************//**
 * \file   UIContext.h
 * \brief  UI用のコンテキスト
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once

#include "Game/Scene/ISceneController.h"
#include "Game/Component/IFloorMeshGetter.h"
#include "Game/Component/PlayerStatusController.h"
#include "Game/Component/EnemyController.h"

/**
 * @brief UI用のコンテキスト
 */
struct  UIContext {

	ISceneController* sceneController = nullptr;				// シーン管理クラス
	IFloorMeshGetter* floorMeshGetter = nullptr;				// 床メッシュ取得コンポーネント
	PlayerStatusController* playerStatusController = nullptr;	// 攻撃可能ボーダーを取得 TODO:インターフェース実装
	EnemyController* enenyController = nullptr;					// 敵の体力を取得 TODO:インターフェース実装

};
