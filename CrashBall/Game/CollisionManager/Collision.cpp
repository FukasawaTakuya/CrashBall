/*****************************************************************//**
 * \file   Collision.h
 * \brief  衝突用の関数一覧
 *
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#include "pch.h"
#include "Collision.h"

using namespace DirectX;


/**
 * \brief 線分と平面の衝突判定
 *
 * \param segment 線分
 * \param plane 平面
 * \return ture 衝突
 */
bool Geometory::IsCollision(Segment* segment, Plane* plane)
{
	SimpleMath::Vector3 point = plane->GetPoint();
	SimpleMath::Vector3 normal = plane->GetNormal();

	// 線分と平面が平行ならfalse
	if (segment->GetVec().Dot(normal) == 0.0f)
	{
		return false;
	}

	SimpleMath::Vector3 v1 = segment->GetPos() - point;
	SimpleMath::Vector3 v2 = (segment->GetPos() + segment->GetVec()) - point;
	// 線分が平面を貫通しているか
	return v1.Dot(normal) * v2.Dot(normal) < 0.0f;
}

/**
 * \brief 線分と三角形の衝突判定
 *
 * \param segment 線分
 * \param triangle 三角形
 * \return ture 衝突
 */
bool Geometory::IsCollision(Segment* segment, Triangle* triangle)
{
	// 線分と平面が衝突してないならfalse
	if (!IsCollision(segment, triangle->GetPlane()))
	{
		return false;
	}

	// 線分と平面の交点
	SimpleMath::Vector3 point
		= CalcIntersection(segment, triangle->GetPlane());

	// 交点が三角形内にあるならtrue
	return IsPointInTriangle(point, triangle);
}

/**
 * \brief 線分とメッシュの当たり判定
 * 
 * \param segment 線分
 * \param mesh メッシュ
 * \return 衝突
 */
bool Geometory::IsCollision(Segment* segment, Mesh* mesh)
{
	// 衝突している面をクリア
	mesh->ClearCollideFace();

	// メッシュの各面と線分の衝突判定
	for (auto& face : mesh->GetFace()) {
		if (Geometory::IsCollision(segment, face.get())) {
			mesh->SetCollideFace(face.get());
		}
	}
	// 衝突している面があるならtrue
	return !mesh->GetCollideFace().empty();
}

/**
 * \brief 線分と球の衝突判定.
 *
 * \param segment	線分
 * \param sphere	球
 * \return ture 衝突
 */
bool Geometory::IsCollision(Segment* segment, Sphere* sphere)
{
	SimpleMath::Vector3 spherePos =
	sphere->GetGameObject()->GetComponent<Transform>()->GetWorldPosition();

	// 線分の始点と球の中心の距離
	float xa = segment->GetPos().x - spherePos.x;
	float ya = segment->GetPos().y - spherePos.y;
	float za = segment->GetPos().z - spherePos.z;

	// 二次方程式の係数
	float a
		= segment->GetVec().Dot(segment->GetVec());
	float b
		= (segment->GetVec().x * xa +
			segment->GetVec().y * ya +
			segment->GetVec().z * za) * 2;
	float c
		= (xa * xa) + (ya * ya) + (za * za) - sphere->GetRadius();

	// 判別式
	float d = (b * b) - 4 * a * c;

	// 判別式が負なら衝突していない
	if (d < 0.0f)
	{
		return false;
	}

	// 判別式の平方根
	d = std::sqrt(d);

	// 二次方程式の解
	float t1 = (-b + d) / (2 * a);
	float t2 = (-b - d) / (2 * a);

	// 解が線分の範囲内にあるなら衝突している
	if ((t1 <= 1.0f && t1 >= 0.0f ||
		t2 <= 1.0f && t2 >= 0.0f)
		&& std::fabsf(t1 - t2) <= 0.5f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * \brief 球と球の衝突判定
 *
 * \param sphere1
 * \param sphere2
 * \return ture 衝突
 */
CollisionInfo Collision::IsCollision(Sphere* sphere1, Sphere* sphere2)
{
	CollisionInfo collsionInfo;

	Transform* transform1 = sphere1->GetGameObject()->GetComponent<Transform>();
	Transform* transform2 = sphere2->GetGameObject()->GetComponent<Transform>();

	// 座標の差
	SimpleMath::Vector3 delta =
		(transform1->GetWorldPosition() - transform2->GetWorldPosition());

	// 半径の和
	float radiusSum = sphere1->GetRadius() + sphere2->GetRadius();

	// 座標の差の長さが半径の和以下ならtrue
	collsionInfo.isCollsion = (delta.Length() <= radiusSum);

	// 衝突している場合
	if (collsionInfo.isCollsion)
	{
		// 各コンポーネントの取得
		Transform* transform1 = sphere1->GetGameObject()->GetComponent<Transform>();
		Transform* transform2 = sphere2->GetGameObject()->GetComponent<Transform>();
		Rigidbody* rigidbody1 = sphere1->GetGameObject()->GetComponent<Rigidbody>();
		Rigidbody* rigidbody2 = sphere2->GetGameObject()->GetComponent<Rigidbody>();

		// 座標の差
		SimpleMath::Vector3 delta = transform1->GetWorldPosition() - transform2->GetWorldPosition();
		// 球から球への方向
		SimpleMath::Vector3 direction = XMVector3Normalize(delta);

		// 半径の和
		float radiusSum = sphere1->GetRadius() + sphere2->GetRadius();

		collsionInfo.direction = direction;
		collsionInfo.overlap = radiusSum - delta.Length();

		collsionInfo.col1 = sphere1;
		collsionInfo.col2 = sphere2;
	}

	return collsionInfo;
}

/**
 * \brief 球と平面の衝突判定
 *
 * \param sphere 球
 * \param plane 平面
 * \return ture 衝突
 */
CollisionInfo Collision::IsCollision(Sphere* sphere, Plane* plane)
{
	CollisionInfo collsionInfo;
	// 球の座標
	SimpleMath::Vector3 spherePos =
		sphere->GetGameObject()->GetComponent<Transform>()->GetWorldPosition();

	// 球と平面の距離を求める
	float distance = plane->CalcLength(spherePos);

	// 距離が球の半径より小さければture
	collsionInfo.isCollsion = (distance <= sphere->GetRadius());

	// 衝突している場合
	if (collsionInfo.isCollsion)
	{
		Transform* transform = sphere->GetGameObject()->GetComponent<Transform>();

		// 球と平面の距離を求める
		float distance = plane->CalcLength(transform->GetWorldPosition());

		collsionInfo.direction = plane->GetNormal();
		collsionInfo.overlap = sphere->GetRadius() - distance;
	}

	return collsionInfo;
}


/**
 * \brief 球と三角形の衝突判定.
 *
 * \param sphere
 * \param triangle
 * \return ture 衝突
 */
CollisionInfo Collision::IsCollision(Sphere* sphere, Triangle* triangle)
{
	CollisionInfo collsionInfo;
		// 球と三角形を含む平面との衝突判定
	if (!IsCollision(sphere, triangle->GetPlane()).isCollsion)
	{
		collsionInfo.isCollsion = false;
		return collsionInfo;
	}

	// 三角形の各頂点
	SimpleMath::Vector3* pos = triangle->GetPoint();
	// 三角形に沿うベクトル
	SimpleMath::Vector3 vec[3];
	vec[0] = pos[1] - pos[0];
	vec[1] = pos[2] - pos[1];
	vec[2] = pos[0] - pos[2];
	// 三角形の各辺
	Segment segments[3];
	for (int i = 0; i < 3; i++) {
		segments[i].SetSegment(pos[i], vec[i]);
	}

	// 有効にすると衝突解決時にガタつくためコメントアウト
	// 各辺と球の衝突判定
	//for (auto seg : segments) {
	//	if (IsCollision(&seg, sphere)) {
	//		return true;
	//	}
	//}

	// 球の座標
	SimpleMath::Vector3 spherePos =
		sphere->GetGameObject()->GetComponent<Transform>()->GetWorldPosition();

	// 平面から球に垂直に伸びる線分
	Segment segment;
	// 線分の設定
	segment.SetSegment(spherePos,
		-triangle->GetPlane()->GetNormal() * sphere->GetRadius() * 1.5f);
	// 線分と三角形の衝突判定
	collsionInfo.isCollsion = Geometory::IsCollision(&segment, triangle);

	// 衝突している場合
	if (collsionInfo.isCollsion)
	{
		collsionInfo = Collision::IsCollision(sphere, triangle->GetPlane());
	}

	return collsionInfo;
}

/**
 * \brief 球とメッシュの衝突判定
 *
 * \param sphere 球
 * \param mesh メッシュ
 * \return ture 衝突
 */
CollisionInfo Collision::IsCollision(Sphere* sphere, Mesh* mesh)
{
	CollisionInfo collsionInfo;
		// 衝突している面をクリア
		mesh->ClearCollideFace();

	// メッシュの各面と球の衝突判定
	for (auto& face : mesh->GetFace()) {
		collsionInfo = Collision::IsCollision(sphere, face.get());
		if (collsionInfo.isCollsion) {
			mesh->SetCollideFace(face.get());
		}
	}
	// 衝突している面があるならtrue
	collsionInfo.isCollsion = !mesh->GetCollideFace().empty();

	// 衝突している場合
	if (collsionInfo.isCollsion)
	{
		// 衝突情報を得るために衝突面ともう一度判定
		collsionInfo = Collision::IsCollision(sphere, mesh->GetCollideFace()[0]);

		collsionInfo.col1 = sphere;
		collsionInfo.col2 = mesh;
	}

	return collsionInfo;
}

/**
 * \brief 球とドームの衝突判定
 * 
 * \param sphere 球
 * \param doom ドーム
 * \return 
 */
CollisionInfo Collision::IsCollision(Sphere* sphere, Doom* doom)
{
	CollisionInfo collsionInfo;
	SimpleMath::Vector3 delta =
		(sphere->GetTransform()->GetWorldPosition() - doom->GetTransform()->GetWorldPosition());

	collsionInfo.isCollsion = (delta.Length() > doom->GetRadius() - sphere->GetRadius()&&
							   delta.Length() < doom->GetRadius() + sphere->GetRadius());

	if (collsionInfo.isCollsion)
	{
		SimpleMath::Vector3 delta =
			(doom->GetTransform()->GetWorldPosition() - sphere->GetTransform()->GetWorldPosition());

		// 許容距離
		float limitDistance = doom->GetRadius() - sphere->GetRadius();

		// 補正距離
		collsionInfo.overlap = delta.Length() - limitDistance;

		// 補正方向
		collsionInfo.direction = XMVector3Normalize(delta);

		collsionInfo.col1 = sphere;
		collsionInfo.col2 = doom;
	}

	return collsionInfo;
}


/**
 * \brief 衝突解決
 * 
 * \param collisionInfo 衝突情報
 */
void Collision::ResolveCollision(CollisionInfo collisionInfo)
{
	// 各コンポーネントの取得
	Transform* transform1 = collisionInfo.col1->GetGameObject()->GetComponent<Transform>();
	Transform* transform2 = collisionInfo.col2->GetGameObject()->GetComponent<Transform>();
	Rigidbody* rigidbody1 = collisionInfo.col1->GetGameObject()->GetComponent<Rigidbody>();
	Rigidbody* rigidbody2 = collisionInfo.col2->GetGameObject()->GetComponent<Rigidbody>();

	float isDynamic1;
	float isDynamic2;
	if (rigidbody1 != nullptr)
	{
		isDynamic1 = rigidbody1->GetIsDynamic() ? 1.0f : 0.0f;
	}
	else
	{
		isDynamic1 = 0.0f;
	}
	if (rigidbody2 != nullptr)
	{
		isDynamic2 = rigidbody2->GetIsDynamic() ? 1.0f : 0.0f;
	}
	else
	{
		isDynamic2 = 0.0f;
	}

	float dynamicSum = isDynamic1 + isDynamic2;

	SimpleMath::Vector3 direction = collisionInfo.direction;
	float overlap = collisionInfo.overlap;

	// 座標の補正
	transform1->Translate( direction * overlap * isDynamic1 / dynamicSum);
	transform2->Translate(-direction * overlap * isDynamic2 / dynamicSum);

	// 速度の補正
	SimpleMath::Vector3 vn1;
	SimpleMath::Vector3 vn2;
	SimpleMath::Vector3 vt1;
	SimpleMath::Vector3 vt2;
	if (rigidbody1 != nullptr)
	{
		vn1 = rigidbody1->GetVelocity().Dot(direction) * direction;
		vt1 = rigidbody1->GetVelocity() - vn1;
	}
	if (rigidbody2 != nullptr)
	{
		vn2 = rigidbody2->GetVelocity().Dot(direction) * direction;
		vt2 = rigidbody2->GetVelocity() - vn2;
	}
	if (rigidbody1)
	{
		rigidbody1->SetVelocity(vn2 + vt1);
	}
	if (rigidbody2)
	{
		rigidbody2->SetVelocity(vn1 + vt2);
	}
}

/**
 * \brief ある点が三角形の内側にあるか.
 *
 * \param point 任意の点
 * \param triangle 三角形
 * \return ture 内側にある
 */
bool IsPointInTriangle(DirectX::SimpleMath::Vector3 point, Triangle* triangle)
{
	// 三角形の各頂点
	SimpleMath::Vector3* pos = triangle->GetPoint();
	// 三角形の法線ベクトル
	SimpleMath::Vector3 normal = triangle->GetPlane()->GetNormal();

	// 各頂点から任意の点へのベクトル
	SimpleMath::Vector3 vt0 = point - pos[0];
	SimpleMath::Vector3 vt1 = point - pos[1];
	SimpleMath::Vector3 vt2 = point - pos[2];

	// 三角形に沿うベクトル
	SimpleMath::Vector3 v0 = pos[1] - pos[0];
	SimpleMath::Vector3 v1 = pos[2] - pos[1];
	SimpleMath::Vector3 v2 = pos[0] - pos[2];

	// 法線ベクトルを求める
	SimpleMath::Vector3 cross0 = vt0.Cross(v0);
	SimpleMath::Vector3 cross1 = vt1.Cross(v1);
	SimpleMath::Vector3 cross2 = vt2.Cross(v2);

	// 法線ベクトルの内積
	float dot0 = cross0.Dot(normal);
	float dot1 = cross1.Dot(normal);
	float dot2 = cross2.Dot(normal);

	// 法線が同じ向きかどうか
	if (dot0 * dot1 >= 0.0f &&
		dot1 * dot2 >= 0.0f &&
		dot2 * dot0 >= 0.0f) return true;
	else return false;
}


/**
 * 直線と平面の交点を求める.
 *
 * \param segment 線分(Rayとして扱う)
 * \param plane 平面
 * \return return 交点
 */
DirectX::SimpleMath::Vector3 CalcIntersection(
	Segment* segment, Plane* plane)
{
	// 線分の始点と平面の距離
	float distance = plane->CalcLength(segment->GetPos());

	// 線分の方向
	SimpleMath::Vector3 direction = segment->GetVec();
	direction.Normalize();

	float dot = direction.Dot(-plane->GetNormal());

	// ベクトルが垂直だった時
	if (dot == 0.0f)
	{
		return SimpleMath::Vector3(1e10f, 1e10f, 1e10f);
	}

	// 直線と平面の交点の距離
	float length = distance / std::abs(dot);

	// 交点を求める
	SimpleMath::Vector3 intersection
		= segment->GetPos() + direction * length;

	return intersection;
}