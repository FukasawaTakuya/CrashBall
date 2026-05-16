#pragma once

#include "Game/Component/Collider.h"

/**
 * @brief 基底オブジェクト
 */
class Sphere
	: public Collider
{
protected:

	Transform* m_transform;	// トランスフォーム

	float m_radius;			// 半径

public:

	// コンストラクタ
	Sphere(Transform* transform, float radius)
		: Collider(ColliderType::Sphere)
		, m_radius{ radius }
		, m_transform{ transform }
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

	// トランスフォームの取得
	Transform* GetTransform() { return m_transform; }

	// 半径の設定
	void SetRadius(float radius) { m_radius = radius; }
};

