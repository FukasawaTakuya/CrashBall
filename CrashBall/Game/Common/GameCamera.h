/*****************************************************************//**
 * \file   GameCamera.h
 * \brief  ゲームカメラ
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once

#include "Game/GameObject/GameObject.h"

#include "Game/Component/Camera/GameCameraController.h"

 /**
 * \brief ゲームカメラ
 */
class  GameCamera : public GameObject {

	// クラス定数の宣言 -------------------------------------------------
private:

	// データメンバの宣言 -----------------------------------------------
protected:

	// コントローラーコンポーネントのキャッシュ
	GameCameraController* m_cameraController = nullptr;
	
	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	GameCamera();

	// デストラクタ
	~GameCamera();

	// 操作
public:

	// 初期化
	void Initialize() override;

	// 更新
	void Update(const GameContext& gameContext) override;

	// 描画
	void Render(const RenderContext& renderContext) override;

	// 終了処理
	void Finalize() override;

	// 取得 / 設定
public:
	// 内部実装
private:
};
