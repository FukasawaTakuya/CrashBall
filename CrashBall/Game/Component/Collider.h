// 多重インクルードの防止 =====================================================
#pragma once

#include "Component.h"
#include "Game/CollisionManager/CollisionLayerMask.h"

class Ball;

class Collider : public Component
{
protected:

	ColliderLayer m_layer;

	ColliderMask m_mask;

public:

	virtual void DrawCollider() {};
};


class Sphere
	: public Collider
{
protected:

	DirectX::SimpleMath::Vector3 m_pos;	// 座標

	float m_radius;						// 半径

public:

	// コンストラクタ
	Sphere(float radius);
	// デストラクタ
	~Sphere() = default;

public:

	// 座標の取得
	DirectX::SimpleMath::Vector3 GetPos() const { return m_pos; }

	// 半径の取得
	float GetRadius() { return m_radius; }

	// 座標の設定
	void SetPos(DirectX::SimpleMath::Vector3 pos) { m_pos = pos; }

	void SetRadius(float radius) { m_radius = radius; }
};

class Plane
	: public Collider
{
private:

	// 平面情報
	DirectX::SimpleMath::Vector4 m_vec4;

	// 
	DirectX::SimpleMath::Vector3 m_point;

public:

	Plane();

	~Plane() = default;

public:

	void Rotate(DirectX::SimpleMath::Matrix rotate);

	float CalcLength(DirectX::SimpleMath::Vector3 point);

public:

	DirectX::SimpleMath::Vector4 GetVec() { return m_vec4; }

	DirectX::SimpleMath::Vector3 GetNormal();

	DirectX::SimpleMath::Vector3 GetSlope();

	DirectX::SimpleMath::Vector3 GetPoint() { return m_point; }

	void SetPlane(
		DirectX::SimpleMath::Vector3 normal,
		DirectX::SimpleMath::Vector3 point);

	void SetPlane(
		DirectX::SimpleMath::Vector3 point1,
		DirectX::SimpleMath::Vector3 point2,
		DirectX::SimpleMath::Vector3 point3);
};

class Triangle
	: public Collider
{
private:

	DirectX::SimpleMath::Vector3 m_point[3];

	DirectX::SimpleMath::Matrix m_rotate;

	Plane m_plane;

public:

	DirectX::SimpleMath::Vector3* GetPoint() {
		return m_point;
	}

	Plane* GetPlane() { return &m_plane; }

	DirectX::SimpleMath::Vector3 GetCenter()
	{
		DirectX::SimpleMath::Vector3 center
		{
			(m_point[0].x + m_point[1].x + m_point[2].x) / 3,
			(m_point[0].y + m_point[1].y + m_point[2].y) / 3,
			(m_point[0].z + m_point[1].z + m_point[2].z) / 3,
		};

		return center;
	}

	void SetTriangle(
		DirectX::SimpleMath::Vector3 point1,
		DirectX::SimpleMath::Vector3 point2,
		DirectX::SimpleMath::Vector3 point3);

	void Rotate(DirectX::SimpleMath::Matrix rotate, DirectX::SimpleMath::Vector3 center);
};

class Segment
	: public Collider
{
private:

	DirectX::SimpleMath::Vector3 m_pos;

	DirectX::SimpleMath::Vector3 m_vec;

public:

	DirectX::SimpleMath::Vector3 GetPos() {
		return m_pos;
	}

	DirectX::SimpleMath::Vector3 GetVec() {
		return m_vec;
	}

	float GetLength() {
		return m_vec.Length();
	}

	void SetSegment(
		DirectX::SimpleMath::Vector3 pos,
		DirectX::SimpleMath::Vector3 vec)
	{
		m_pos = pos;
		m_vec = vec;
	}
};

class Mesh
	: public Collider
{
private:
	// メッシュ
	std::vector<std::unique_ptr<Triangle>> m_faces;

	DirectX::SimpleMath::Vector3 m_position;

	float m_scale = 1.0f;

	std::vector<Triangle*> m_hitFace;

public:
	bool LoadObjData(const wchar_t* filename);

	bool IsCollision(Sphere* sphere);

	std::vector<std::unique_ptr<Triangle>>& GetFace() { return m_faces; }
	const std::vector<Triangle*>& GetHitFace() { return m_hitFace; }

	void SetScale(float scale) {
		m_scale = scale;
	}

	void SetHitFace(Triangle* face)
	{
		m_hitFace.emplace_back(face);
	}
	void ClearHitFace()
	{
		m_hitFace.clear();
	}

	Triangle* GetFace(int index)
	{
		return m_faces[index].get();
	}

	void Rotate(DirectX::SimpleMath::Matrix rotate);
};
