/*****************************************************************//**
 * \file   Plane.h
 * \brief  平面
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Collider/Collider.h"


/**
 * \brief 平面
 */
class Plane
{

	// データメンバの宣言 -----------------------------------------------
private:

	DirectX::SimpleMath::Vector4 m_vec4;	// 平面情報
	DirectX::SimpleMath::Vector3 m_normal;	// 法線ベクトル

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	Plane();

	~Plane() = default;

	// 操作
public:

	// 回転
	void Rotate(DirectX::SimpleMath::Matrix rotate);

	// ある点との最短距離を求める
	float CalcLength(DirectX::SimpleMath::Vector3 point) const;

	// 取得 / 設定
public:

	// 法線の取得
	DirectX::SimpleMath::Vector3 GetNormal() const { return m_normal; }

	// 平面の設定
	void SetPlane(
		DirectX::SimpleMath::Vector3 normal,
		DirectX::SimpleMath::Vector3 point);

	// 平面の設定
	void SetPlane(
		DirectX::SimpleMath::Vector3 point1,
		DirectX::SimpleMath::Vector3 point2,
		DirectX::SimpleMath::Vector3 point3);
};
