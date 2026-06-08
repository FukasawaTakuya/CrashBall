/*****************************************************************//**
 * \file   FloorMeshGauge.h
 * \brief  
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once

#include "Game/Component/IFloorMeshGetter.h"
#include "Game/GameObject/GameObject.h"

/**
 * @brief 
 */
class  FloorMeshGauge : public GameObject {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	IFloorMeshGetter* floorMeshGetter = nullptr;	// 床メッシュ取得コンポーネント


	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	FloorMeshGauge();

	// デストラクタ
	~FloorMeshGauge();

	// 操作
public:

	// 取得/設定
public:

	// 内部実装
private:

};
