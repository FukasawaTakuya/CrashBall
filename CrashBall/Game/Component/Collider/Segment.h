/*****************************************************************//**
 * \file   Segment.h
 * \brief  線分クラスに関するヘッダーファイル
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/
#pragma once

#include "Game/Component/Collider.h"

/**
 * @brief 線分クラス
 */
class Segment
{
private:

	// 始点
	DirectX::SimpleMath::Vector3 m_pos;

	// 終点までのベクトル
	DirectX::SimpleMath::Vector3 m_vec;

public:

	// コンストラクタ
	Segment() = default;

public:

	// 始点の取得
	DirectX::SimpleMath::Vector3 GetPos() const 
	{
		return m_pos;
	}

	// 終点までのベクトルの取得
	DirectX::SimpleMath::Vector3 GetVec() const 
	{
		return m_vec;
	}

	// 長さの取得
	float GetLength() {
		return m_vec.Length();
	}

	// 線分の設定
	void SetSegment(
		DirectX::SimpleMath::Vector3 pos,
		DirectX::SimpleMath::Vector3 vec)
	{
		m_pos = pos;
		m_vec = vec;
	}
};
