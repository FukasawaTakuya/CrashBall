/*****************************************************************//**
 * \file   GameCameraController.h
 * \brief  ゲームカメラ操作コンポーネント
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"

#include "TargetCamera.h"

/**
 * @brief ゲームカメラ操作コンポーネント
 */
class  GameCameraController : public Component {

	// クラス定数の宣言 -------------------------------------------------
private:

	static constexpr float ROTATE_ANGELRAD = DirectX::XM_PIDIV4;	// 回転角度

	// データメンバの宣言 -----------------------------------------------
private:

	// ターゲットカメラコンポーネントのキャッシュ
	TargetCamera* m_targetCamera = nullptr;		

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	GameCameraController(IGameObject* gameObejct);

	// デストラクタ
	~GameCameraController();

	// 操作
public:

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 取得/設定
public:

	void Test();

	// 内部実装
private:

};
