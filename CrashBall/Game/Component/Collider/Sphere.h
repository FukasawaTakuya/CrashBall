// 多重インクルードの防止 =====================================================
#pragma once




// ヘッダファイルの読み込み ===================================================
#include "Game/Component/Collider.h"
// クラスの前方宣言 ===================================================



// クラスの定義 ===============================================================
/**
 * @brief 基底オブジェクト
 */
class Sphere
	: public Collider
{
protected:

	Transform* m_transform;	// 座標

	float m_radius;			// 半径

public:

	// コンストラクタ
	Sphere(Transform* transform, float radius);
	// デストラクタ
	~Sphere() = default;

public:

	void DrawCollider() override {};

	bool OnCollide(Collider* collider) override;

	bool OnCollideWith(Sphere* sphere) override;

	bool OnCollideWith(Mesh* mash) override;



	// 座標の取得
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_transform->GetPosition(); }

	// 半径の取得
	float GetRadius() const { return m_radius; }

	Transform* GetTransform() { return m_transform; }

	void SetRadius(float radius) { m_radius = radius; }
};

