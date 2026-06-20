/*****************************************************************//**
 * \file   Camera.h
 * \brief  ゲームカメラ
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once
#include "Game/Component/Default/Transform.h"

#include "Game/GameObject/GameObject.h"

#include "Game/Component/TargetCamera.h"
#include "Game/Component/GameCameraController.h"

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

	void Update(const GameContext& gameContext) override;

	void Render(const RenderContext& renderContext) override;

	void Finalize() override;

	// 取得 / 設定
public:
	// 内部実装
private:
};
