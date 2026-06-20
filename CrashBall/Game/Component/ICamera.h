/*****************************************************************//**
 * \file   ICamera.h
 * \brief  カメラコンポーネントのインターフェース
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once
#include "SimpleMath.h"

/**
 * @brief カメラコンポーネントのインターフェース
 */
class  ICamera {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:



	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	ICamera() = default;

	// デストラクタ
	virtual ~ICamera() = default;

	// 操作
public:

	// 取得/設定
public:

	// ビュー行列の取得
	virtual DirectX::SimpleMath::Matrix GetView() const = 0;

	// 前方向(XZ平面)の取得
	virtual DirectX::SimpleMath::Vector3 GetForward() const = 0;

	// 右方向(XZ平面)の取得
	virtual DirectX::SimpleMath::Vector3 GetRight() const = 0;


	// 内部実装
private:

};
