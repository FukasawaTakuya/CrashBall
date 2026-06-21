/*****************************************************************//**
 * \file   Segment.h
 * \brief  線分 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/
#pragma once

#include "Game/Component/Default/Collider/Collider.h"

/**
 * @brief 線分
 */
class Segment
{

	// データメンバの宣言 -----------------------------------------------
private:

	// 始点
	DirectX::SimpleMath::Vector3 m_pos;

	// 終点までのベクトル
	DirectX::SimpleMath::Vector3 m_vec;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Segment() = default;

	// 取得/設定
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
