#pragma once

#include "Game/Component/Collider.h"

class Plane
{
private:

	DirectX::SimpleMath::Vector4 m_vec4;	// 平面情報
	DirectX::SimpleMath::Vector3 m_normal;	// 法線ベクトル

public:

	Plane();

	~Plane() = default;

public:

	// 回転
	void Rotate(DirectX::SimpleMath::Matrix rotate);

	// ある点との最短距離を求める
	float CalcLength(DirectX::SimpleMath::Vector3 point) const;

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
