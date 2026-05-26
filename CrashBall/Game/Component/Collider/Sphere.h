#pragma once

#include "Game/Component/Collider.h"

/**
 * @brief 基底オブジェクト
 */
class Sphere
	: public Collider
{
private:

	float m_radius;			// 半径

public:

	// コンストラクタ
	Sphere(float radius)
		: Collider(ColliderType::Sphere)
		, m_radius{ radius }
	{}

	// デストラクタ
	~Sphere() = default;

public:

	// コライダーの描画
	void DrawCollider() override {};

	// 座標の取得
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_transform->GetPosition(); }

	// 半径の取得
	float GetRadius() const { return m_radius; }

	// 半径の設定
	void SetRadius(float radius) { m_radius = radius; }
};

