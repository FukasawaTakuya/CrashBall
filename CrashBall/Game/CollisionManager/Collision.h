#pragma once

#include "Game/Component/Default/Collider/Collider.h"
#include "Game/Component/Default/Transform.h"
#include "Game/Component/Default/RigidBody.h"

#include "Game/Component/Default/Collider/Sphere.h"
#include "Game/Component/Default/Collider/Plane.h"
#include "Game/Component/Default/Collider/Triangle.h"
#include "Game/Component/Default/Collider/Segment.h"
#include "Game/Component/Default/Collider/Mesh.h"

#include "Game/GameObject/GameObject.h"

namespace Collision {

	// 線分と直線の衝突判定
	bool IsCollision(Segment* segment, Plane* plane);
	bool IsCollision(Segment* segment, DirectX::SimpleMath::Vector3 intersection);

	// 線分と三角形の衝突判定
	bool IsCollision(Segment* segment, Triangle* triangle);

	// 線分と球の衝突判定
	bool IsCollision(Segment* segment, Sphere* sphere);

	// 球と球の衝突判定
	bool IsCollision(Sphere* sphere1, Sphere* sphere2);

	// 球と平面の衝突判定
	bool IsCollision(Sphere* sphere, Plane* plane);
	bool IsCollision(Plane* plane, Sphere* sphere);

	// 球と三角形の衝突判定
	bool IsCollision(Sphere* sphere, Triangle* triangle);

	// 球とメッシュの衝突判定
	bool IsCollision(Sphere* sphere, Mesh* mesh);
	bool IsCollision(Mesh* mesh, Sphere* sphere);



	// 球と平面の衝突解決
	void ResolveCollision(Sphere* sphere, Plane* plan);

	// 球とメッシュの衝突解決
	void ResolveCollision(Sphere* sphere, Mesh* mesh);

	// 球と球の衝突解決
	void ResolveCollision(Sphere* sphere1, Sphere* sphere2);
}


// ある点が三角形の内側にあるか判定
bool IsPointInTriangle(DirectX::SimpleMath::Vector3 point, Triangle* triangle);
// 直線と平面の交点を求める
DirectX::SimpleMath::Vector3 CalcIntersection(Segment* segment, Plane* plane);

DirectX::SimpleMath::Vector4 ConvertVector4(DirectX::SimpleMath::Vector3 v3);
DirectX::SimpleMath::Vector3 ConvertVector3(DirectX::SimpleMath::Vector4 v3);

