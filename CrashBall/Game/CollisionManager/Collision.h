#pragma once

#include "Game/Component/Collider.h"

namespace Collision {

	// 球と平面の衝突判定
	bool IsCollision(Sphere* sphere, Plane* plane);
	bool IsCollision(Plane* plane, Sphere* sphere);

	// 線分と直線の衝突判定
	bool IsCollision(Segment* segment, Plane* plane);
	bool IsCollision(Segment* segment, DirectX::SimpleMath::Vector3 intersection);

	// 線分と三角形の衝突判定
	bool IsCollision(Segment* segment, Triangle* triangle);

	// 線分と球の衝突判定
	bool IsCollision(Segment* segment, Sphere* sphere);

	// 球と三角形の衝突判定
	bool IsCollision(Sphere* sphere, Triangle* triangle);

	bool IsCollision(Sphere* sphere, Mesh* mesh);


	//// 球と平面の衝突解決
	//void ResolveCollision(Ball* ball, Plane* plan);
}


// ある点が三角形の内側にあるか判定
bool IsPointInTriangle(DirectX::SimpleMath::Vector3 point, Triangle* triangle);
// 直線と平面の交点を求める
DirectX::SimpleMath::Vector3 CalcIntersection(Segment* segment, Plane* plane);

DirectX::SimpleMath::Vector4 ConvertVector4(DirectX::SimpleMath::Vector3 v3);
DirectX::SimpleMath::Vector3 ConvertVector3(DirectX::SimpleMath::Vector4 v3);

