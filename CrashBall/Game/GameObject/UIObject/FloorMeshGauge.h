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
#include <Game/Component/FloorMeshGaugeController.h>

/**
 * @brief 
 */
class  FloorMeshGauge : public GameObject {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	FloorMeshGaugeController* m_floorMeshGaugeController;

	IFloorMeshGetter* floorMeshGetter = nullptr;	// 床メッシュ取得コンポーネント


	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	FloorMeshGauge();

	// デストラクタ
	~FloorMeshGauge();

	// 初期化
	void Initialize();

	// 更新
	void Update(const GameContext& gameContext);

	// 描画
	void Render(const RenderContext& renderContext);

	// 終了処理
	void Finalize();


	// 操作
public:

	// 取得/設定
public:

	// 内部実装
private:

};
