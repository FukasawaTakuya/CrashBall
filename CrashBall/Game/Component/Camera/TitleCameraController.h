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

using namespace DirectX;

/**
 * @brief 基底タイトルカメラ操作コンポーネント
 */
class  TitleCameraController : public Component
{

	// クラス定数の宣言 -------------------------------------------------
private:

	// 1秒間の回転量
	float m_rotateAngeleRad;

	// データメンバの宣言 -----------------------------------------------
private:

	// コンポーネントのキャッシュ
	TargetCamera* m_targetCamera = nullptr;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// デフォルトコンストラクタ
	TitleCameraController() = default;

	// コンストラクタ
	TitleCameraController(IGameObject* gameObject);

	// コピーコンストラクタ
	TitleCameraController(
		IGameObject* gameObject,
		const TitleCameraController& other
	);

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

	// JsonConverter
private:

	friend void from_json(const json& j, TitleCameraController& titleCameraController);
	friend void to_json(json& j, const TitleCameraController& titleCameraController);

	// 演算子オーバーロード
public:

	void operator=(const TitleCameraController& other)
	{
		m_rotateAngeleRad = other.m_rotateAngeleRad;
	}

};
