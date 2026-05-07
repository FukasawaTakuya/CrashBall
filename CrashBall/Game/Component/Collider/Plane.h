// 多重インクルードの防止 =====================================================
#pragma once




// ヘッダファイルの読み込み ===================================================
#include "Game/Component/Collider.h"
// クラスの前方宣言 ===================================================



// クラスの定義 ===============================================================
class Plane
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
