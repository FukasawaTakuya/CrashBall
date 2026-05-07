// 多重インクルードの防止 =====================================================
#pragma once




// ヘッダファイルの読み込み ===================================================
#include "Game/Component/Collider.h"
#include "Triangle.h"
#include "Sphere.h"
// クラスの前方宣言 ===================================================



// クラスの定義 ===============================================================
/**
 * @brief 基底オブジェクト
 */
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

	Mesh();

	void DrawCollider() override {}

public:
	bool LoadObjData(const wchar_t* filename);

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
