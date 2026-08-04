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
class  DebugCameraController : public TargetCameraController
{
	// データメンバの宣言 -----------------------------------------------
private:

	// カメラの照準
	std::unique_ptr<Transform> m_targetTransform;

	// プロパティの設定
	BeginProperty()
	EndProperty()

	// コンポーネント名の設定
	SetCompName("DefaultCameraController")


	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	DebugCameraController(IGameObject* gameObject);

	// デストラクタ
	~DebugCameraController();

	// 操作
public:

	// 更新
	void Update(const GameContext& gameContext) override;

	// 取得/設定
public:

	// 内部実装
private:

	// プロパティの取得
	const std::vector<PropertyInfo>& GetProperties() const override
	{
		return m_properties;
	}

	// コンポーネント名の取得
	std::string GetCompName() const override
	{
		return m_compName;
	}

};
