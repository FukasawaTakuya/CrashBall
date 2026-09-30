/*****************************************************************//**
 * \file   Collision.h
 * \brief  衝突用の関数一覧
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Collider/Collider.h"
#include "Game/Component/Default/Physics/Transform.h"
#include "Game/Component/Default/Physics/RigidBody.h"

#include "Game/Component/Default/Collider/Sphere.h"
#include "Game/Component/Default/Collider/Mesh.h"
#include "Game/Component/Default/Collider/Doom.h"

#include "Game/Geometory/Plane.h"
#include "Game/Geometory/Triangle.h"
#include "Game/Geometory/Segment.h"

#include "Game/GameObject/GameObject.h"

// 衝突情報
struct CollisionInfo
{
	bool isCollsion = false;
	float overlap = 0.0f;
	DirectX::SimpleMath::Vector3 direction;
	Collider* col1 = nullptr;
	Collider* col2 = nullptr;
};

namespace Geometory
{
	// 線分と平面の衝突判定
	bool IsCollision(Segment* segment, Plane* plane);

	// 線分と三角形の衝突判定
	bool IsCollision(Segment* segment, Triangle* triangle);

	// 線分とメッシュの衝突判定
	bool IsCollision(Segment* segment, Mesh* mesh);

	// 線分と球の衝突判定
	bool IsCollision(Segment* segment, Sphere* sphere);
}

namespace Collision {

	// 球と球の衝突判定
	CollisionInfo IsCollision(Sphere* sphere1, Sphere* sphere2);

	// 球と平面の衝突判定
	CollisionInfo IsCollision(Sphere* sphere, Plane* plane);

	// 球と三角形の衝突判定
	CollisionInfo IsCollision(Sphere* sphere, Triangle* triangle);

	// 球とメッシュの衝突判定
	CollisionInfo IsCollision(Sphere* sphere, Mesh* mesh);

	// 球とドームの衝突判定
	CollisionInfo IsCollision(Sphere* sphere, Doom* doom);

	// 衝突解決
	void ResolveCollision(CollisionInfo collisionInfo);
}


// ある点が三角形の内側にあるか判定
bool IsPointInTriangle(DirectX::SimpleMath::Vector3 point, Triangle* triangle);
// 直線と平面の交点を求める
DirectX::SimpleMath::Vector3 CalcIntersection(Segment* segment, Plane* plane);

DirectX::SimpleMath::Vector4 ConvertVector4(DirectX::SimpleMath::Vector3 v3);
DirectX::SimpleMath::Vector3 ConvertVector3(DirectX::SimpleMath::Vector4 v3);

