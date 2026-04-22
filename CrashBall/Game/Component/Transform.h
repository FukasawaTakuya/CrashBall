/*****************************************************************//**
 * \file   Transform.h
 * \brief  トランスフォームに関するヘッダーファイル
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

// 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include "Component.h"
// クラスの前方宣言 ===================================================



// クラスの定義 ===============================================================
/**
 * @brief 基底オブジェクト
 */
class  Transform : public Component 
{

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	DirectX::SimpleMath::Vector3 m_position;	// 移動

	DirectX::SimpleMath::Matrix m_rotate;		// 回転

	DirectX::SimpleMath::Quaternion m_quaternion;

	float m_scale = 1.0f;						// スケール


	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Transform();

	// デストラクタ
	~Transform();

	// 操作
public:

	// 移動
	void Translate(DirectX::SimpleMath::Vector3 trans);

	// 回転
	void Rotate(DirectX::SimpleMath::Matrix rotate);

	// クオータニオンによる回転
	void RotateQuaternion(
		const DirectX::SimpleMath::Quaternion& quaternion);


	// 取得/設定
public:

	// ポジションの取得
	DirectX::SimpleMath::Vector3 GetPosition() const
	{
		return m_position;
	}

	// 回転の取得
	DirectX::SimpleMath::Matrix GetRotate() const
	{
		return m_rotate;
	}

	// クオータニオンの取得
	DirectX::SimpleMath::Quaternion GetQuaternion() const
	{
		return m_quaternion;
	}

	// スケールの取得
	float GetScale() const
	{
		return m_scale;
	}

	// ポジションのセット
	void SetPosition(DirectX::SimpleMath::Vector3 position)
	{
		m_position = position;
	}

	// 回転のセット
	void SetRotate(DirectX::SimpleMath::Matrix rotate)
	{
		m_rotate = rotate;
	}

	// スケールのセット
	void SetScale(float scale)
	{
		m_scale = scale;
	}

	// 内部実装
private:

};
