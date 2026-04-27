// 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include "Game/Component/Collider.h"
// クラスの前方宣言 ===================================================


// クラスの定義 ===============================================================
/**
 * @brief 基底オブジェクト
 */
class Segment
	: public Collider
{
private:

	DirectX::SimpleMath::Vector3 m_pos;

	DirectX::SimpleMath::Vector3 m_vec;

public:

	Segment();

	void DrawCollider() override {};

	bool OnCollide(Collider* collider) override { return false; }

	bool OnCollideWith(Sphere* sphere) override { return false; }

	bool OnCollideWith(Mesh* mash) override { return false; }



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
