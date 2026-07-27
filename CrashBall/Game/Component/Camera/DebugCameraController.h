/*****************************************************************//**
 * \file   DebugCameraController.h
 * \brief  デバッグ用カメラ操作コンポーネント
 * 
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Camera/TargetCameraController.h"

/**
 * \brief デバッグ用カメラ操作コンポーネント
 */
class  DebugCameraController 
	: public Component<TargetCameraController>
	, public TargetCameraController
{
	// データメンバの宣言 -----------------------------------------------
private:

	// カメラの照準
	std::unique_ptr<Transform> m_targetTransform;

	// プロパティの設定
	BeginProperty()
	EndProperty()


	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	DebugCameraController(IGameObject* gameObject);

	// デストラクタ
	~DebugCameraController();

	// 操作
public:

	void Initialize();

	// 更新
	void Update();

	// 取得/設定
public:

	// 内部実装
private:

	// プロパティの取得
	const std::vector<PropertyInfo>& GetProperties() const override
	{
		return m_properties;
	}
};
