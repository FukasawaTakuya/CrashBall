/*****************************************************************//**
 * \file   Sphere.h
 * \brief  球コライダー
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Collider/Collider.h"

/**
 * \brief 球コライダー
 */
class Sphere
	: public Collider
{
private:

	float m_radius;	// 半径

public:

	// デフォルトコンストラクタ
	Sphere() = default;

	// コンストラクタ
	Sphere(IGameObject* gameObject, float radius);

	// コピーコンストラクタ
	Sphere(IGameObject* gameObject, const Sphere& sphere);


	// デストラクタ
	~Sphere();

public:

	// コライダーの描画
	void DrawCollider() override {};

	// 座標の取得
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_transform->GetPosition(); }

	// 半径の取得
	float GetRadius() const { return m_radius * m_transform->GetMaxScale(); }

	// 半径の設定
	void SetRadius(float radius) { m_radius = radius; }

	// JsonConvert
private:
	friend void from_json(const json& j, Sphere& sphere);
	friend void to_json(json& j, const Sphere& sphere);

};

