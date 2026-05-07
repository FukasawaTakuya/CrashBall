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
{
private:

	DirectX::SimpleMath::Vector3 m_pos;

	DirectX::SimpleMath::Vector3 m_vec;

public:

	Segment();

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
