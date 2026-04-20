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

	float m_scale = 1.0f;						// 拡大


	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Transform();

	// デストラクタ
	~Transform();

	// 操作
public:

	void Translate(DirectX::SimpleMath::Vector3 trans);

	// 回転
	void Rotate(DirectX::SimpleMath::Matrix rotate);

	void RotateQuaternion(
		const DirectX::SimpleMath::Quaternion& quaternion);


	// 取得/設定
public:

	DirectX::SimpleMath::Vector3 GetPosition() const
	{
		return m_position;
	}

	DirectX::SimpleMath::Matrix GetRotate()
	{
		return m_rotate;
	}

	DirectX::SimpleMath::Quaternion GetQuaternion()
	{
		return m_quaternion;
	}

	float GetScale() const
	{
		return m_scale;
	}



	void SetPosition(DirectX::SimpleMath::Vector3 position)
	{
		m_position = position;
	}

	void SetRotate(DirectX::SimpleMath::Matrix rotate)
	{
		m_rotate = rotate;
	}

	void SetScale(float scale)
	{
		m_scale = scale;
	}

	// 内部実装
private:

};
