/*****************************************************************//**
 * \file   TitleCameraController.h
 * \brief  タイトルカメラ操作コンポーネント
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"
#include "Game/Component/Camera/ICamera.h"
#include "TargetCamera.h"

/**
 * @brief 基底タイトルカメラ操作コンポーネント
 */
class  TitleCameraController : public Component
{

	// クラス定数の宣言 -------------------------------------------------
private:

	static constexpr float ROTATE_ANGLERAD = XM_PIDIV4 / 3.0f;

	// データメンバの宣言 -----------------------------------------------
private:

	TargetCamera* m_targetCamera = nullptr;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	TitleCameraController(IGameObject* gameObject);

	// デストラクタ
	~TitleCameraController();

	// 操作
public:

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 取得/設定
public:

	// 内部実装
private:

};
