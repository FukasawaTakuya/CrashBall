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

	// データメンバの宣言 -----------------------------------------------
private:

	// カメラ操作コンポーネントのキャッシュ
	DebugCameraController* m_cameraController = nullptr;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	DebugCamera();

	// デストラクタ
	~DebugCamera();

	// 操作
public:

	// 初期化
	void Start() override;

	// 更新
	void Update(const GameContext& gameContext) override;

	// 描画
	void Render(const RenderContext& renderContext) override;

	// 終了処理
	void Finalize() override;

	// パラメータの書き込み
	void SaveParam() override;

	// データの再読み込み
	void ReloadParam() override;


	// 取得/設定
public:

	// 内部実装
private:

};
