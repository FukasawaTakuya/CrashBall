#pragma once

#include "Game/Component/Default/Collider/Collider.h"
#include "Plane.h"

using namespace nlohmann;

/**
 * @brief 三角形
 */
class Triangle
{
	// データメンバの宣言 -----------------------------------------------
private:

	DirectX::SimpleMath::Vector3 m_point[3];	// 頂点

	std::unique_ptr<Plane> m_plane;				// 平面情報

	DirectX::SimpleMath::Vector3 m_initPoint[3];// 初期頂点

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Triangle();

	// Jsonから読み込んだ時用のコンストラクタ
	Triangle(
		const Triangle& triangle, 
		const DirectX::SimpleMath::Vector3& scale);

	// 操作
public:

	// 回転
	void Rotate(
		const DirectX::SimpleMath::Quaternion& rotate,
		const DirectX::SimpleMath::Vector3& basePosition
	);

	// スケーリング
	void Scale(DirectX::SimpleMath::Vector3& scale);

	// 取得/設定
public:

	// 頂点の取得
	DirectX::SimpleMath::Vector3* GetPoint()
	{
		return m_point;
	}

	// 平面情報の取得
	Plane* GetPlane() { return m_plane.get(); }

	//　中心の取得
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

	// 三角形の設定
	void SetTriangle(
		DirectX::SimpleMath::Vector3 point1,
		DirectX::SimpleMath::Vector3 point2,
		DirectX::SimpleMath::Vector3 point3);

public:
	// Jsonから三角形への変換
	friend void from_json(const json& j, Triangle& triangle);
};