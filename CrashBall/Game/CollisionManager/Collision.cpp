#include "pch.h"
#include "Collision.h"

using namespace DirectX;

/**
 * \brief 球と平面の衝突判定
 *
 * \param sphere 球
 * \param plane 平面
 * \return
 */
bool Collision::IsCollision(Sphere* sphere, Plane* plane)
{
	// 球と平面の距離を求める
	float distance = plane->CalcLength(sphere->GetPosition());

	// 距離が球の半径より小さければture
	bool r = (distance <= sphere->GetRadius());

	return r;
}
bool Collision::IsCollision(Plane* plane, Sphere* sphere)
{
	return IsCollision(sphere, plane);
}


/**
 * \brief 線分と平面の衝突判定
 * 
 * \param segment 線分
 * \param plane 平面
 * \return 
 */
bool Collision::IsCollision(Segment* segment, Plane* plane)
{
	// 直線と平面の交点
	SimpleMath::Vector3 point =
		CalcIntersection(segment, plane);

	// 交点から平面との衝突判定を行う
	return IsCollision(segment, point);
}

/**
 * \brief 線分と平面の衝突判定(交点から求める)
 * 
 * \param segment 線分
 * \param intersection 平面との交点 
 * \return 
 */
bool Collision::IsCollision(
	Segment* segment, 
	DirectX::SimpleMath::Vector3 intersection) 
{ 
	// 交点と線分の両端の距離が線分の長さ以下ならtrue
	if ((intersection - segment->GetPos()).Length() <= segment->GetLength() &&
		(intersection - (segment->GetPos() + segment->GetVec())).Length() <= segment->GetLength()) {
		return true; 
	}
	else return false; 
}

/**
 * \brief 線分と三角形の衝突判定
 * 
 * \param segment 線分
 * \param triangle 三角形
 * \return 
 */
bool Collision::IsCollision(Segment* segment, Triangle* triangle)
{
	// 線分と平面の交点
	SimpleMath::Vector3 point
		= CalcIntersection(segment, triangle->GetPlane());

	// 線分と平面が衝突してないならfalse
	if (!IsCollision(segment, point)) {
		return false;
	}

	// 交点が三角形内にあるならtrue
	return IsPointInTriangle(point, triangle);
}

/**
 * \brief 線分と球の衝突判定.
 * 
 * \param segment	線分
 * \param sphere	球
 * \return 
 */
bool Collision::IsCollision(Segment* segment, Sphere* sphere)
{
	// 線分の始点と球の中心の距離
	float xa = segment->GetPos().x - sphere->GetPosition().x;
	float ya = segment->GetPos().y - sphere->GetPosition().y;
	float za = segment->GetPos().z - sphere->GetPosition().z;

	// 二次方程式の係数
	float a
		= std::pow(segment->GetVec().x, 2) 
		+ std::pow(segment->GetVec().y, 2) 
		+ std::pow(segment->GetVec().z, 2);
	float b
		= ( segment->GetVec().x * xa +
			segment->GetVec().y * ya +
			segment->GetVec().z * za ) * 2;
	float c
		= std::pow(xa, 2) + std::pow(ya, 2) + std::pow(za, 2) - sphere->GetRadius();

	// 判別式
	float d = std::pow(b, 2) - 4 * a * c;

	// 判別式が負なら衝突していない
	if (d < 0.0f) return false;

	// 判別式の平方根
	d = std::sqrt(d);

	// 二次方程式の解
	float t1 = (-b + d) / (2 * a);
	float t2 = (-b - d) / (2 * a);

	// 解が線分の範囲内にあるなら衝突している
	if (t1 <= 1.0f && t1 >= 0.0f ||
		t2 <= 1.0f && t2 >= 0.0f)
	{
		return true;
	}
	else return false;
}

/**
 * \brief 球と球の衝突判定
 * 
 * \param sphere1
 * \param sphere2
 * \return 
 */
bool Collision::IsCollision(Sphere* sphere1, Sphere* sphere2)
{
	// 座標の差
	SimpleMath::Vector3 delta =
		(sphere1->GetTransform()->GetPosition() - sphere2->GetTransform()->GetPosition());

	// 半径の和
	float radiusSum = sphere1->GetRadius() + sphere2->GetRadius();

	// 座標の差の長さが半径の和以下ならtrue
	return (delta.Length() <= radiusSum);
}


/**
 * \brief 球と三角形の衝突判定.
 * 
 * \param sphere
 * \param triangle
 * \return 
 */
bool Collision::IsCollision(Sphere* sphere, Triangle* triangle)
{
	// 球と三角形を含む平面との衝突判定
	if (!IsCollision(sphere, triangle->GetPlane())) return false;

	// 三角形の各頂点
	SimpleMath::Vector3* pos = triangle->GetPoint();
	// 三角形に沿うベクトル
	SimpleMath::Vector3 vec[3];
	vec[0] = pos[1] - pos[0];
	vec[1] = pos[2] - pos[1];
	vec[2] = pos[0] - pos[2];
	// 三角形の各辺
	Segment segments[3];
	for (int i = 0; i < 3;i++) {
		segments[i].SetSegment(pos[i], vec[i]);
	}

	// 有効にすると衝突解決時にガタつくためコメントアウト
	// 各辺と球の衝突判定
	//for (auto seg : segments) {
	//	if (IsCollision(&seg, sphere)) {
	//		return true;
	//	}
	//}

	// 平面から球に垂直に伸びる線分
	Segment segment;
	// 線分の設定
	segment.SetSegment(sphere->GetPosition(), 
		-triangle->GetPlane()->GetNormal() * sphere->GetRadius() * 1.5f);

	// 線分と三角形の衝突判定
	return IsCollision(&segment, triangle);
}

/**
 * \brief 球とメッシュの衝突判定
 * 
 * \param sphere
 * \param mesh
 * \return 
 */
bool Collision::IsCollision(Sphere* sphere, Mesh* mesh)
{
	// 衝突している面をクリア
	mesh->ClearCollideFace();

	// メッシュの各面と球の衝突判定
	for (auto& face : mesh->GetFace()) {
		if (Collision::IsCollision(sphere, face.get())) {
			mesh->SetCollideFace(face.get());
		}
	}
	// 衝突している面があるならtrue
	return !mesh->GetCollideFace().empty();
}
bool Collision::IsCollision(Mesh* mesh, Sphere* sphere)
{
	return IsCollision(sphere, mesh);
}


/**
 * \brief 球と平面の衝突の解決
 *
 * \param sphere 球
 * \param plane 平面
 */
void Collision::ResolveCollision(Sphere* sphere, Plane* plane)
{
	Transform*	transform = sphere->GetOwner()->GetComponent<Transform>();
	RigidBody*	rigidbody = sphere->GetOwner()->GetComponent<RigidBody>();
	Sphere*		collider = sphere->GetOwner()->GetComponent<Sphere>();

	// 球と平面の距離を求める
	float distance = plane->CalcLength(transform->GetPosition());

	// 補正距離を求める
	float overlap = collider->GetRadius() - distance;

	// 補正方向
	DirectX::SimpleMath::Vector3 direction = plane->GetNormal();

	transform->Translate(direction * overlap);

	// 法線ベクトル
	SimpleMath::Vector3 vn = rigidbody->GetVelocity().Dot(direction) * direction;
	// 接線ベクトル
	SimpleMath::Vector3 vt = rigidbody->GetVelocity() - vn;

	rigidbody->SetVelocity(vt);
}

/**
 * \brief 球とメッシュの衝突解決
 * 
 * \param sphere 球
 * \param mesh メッシュ
 */
void Collision::ResolveCollision(Sphere* sphere, Mesh* mesh)
{
	for (auto hitFace : mesh->GetCollideFace())
	{
		Collision::ResolveCollision(sphere, hitFace->GetPlane());
	}
}

/**
 * \brief 球と球の衝突解決.
 * 
 * \param sphere1
 * \param sphere2
 */
void Collision::ResolveCollision(Sphere* sphere1, Sphere* sphere2)
{
	// 各コンポーネントの取得
	Transform* transform1 = sphere1->GetOwner()->GetComponent<Transform>();
	Transform* transform2 = sphere2->GetOwner()->GetComponent<Transform>();
	RigidBody* rigidbody1 = sphere1->GetOwner()->GetComponent<RigidBody>();
	RigidBody* rigidbody2 = sphere2->GetOwner()->GetComponent<RigidBody>();

	// 座標の差
	SimpleMath::Vector3 delta = sphere1->GetPosition() - sphere2->GetPosition();
	// 球から球への方向
	SimpleMath::Vector3 direction = XMVector3Normalize(delta);

	// 半径の和
	float radiusSum = sphere1->GetRadius() + sphere2->GetRadius();

	// 座標の補正
	 transform1->Translate( direction * (radiusSum- delta.Length()) / 2.0f);
	 transform2->Translate(-direction * (radiusSum- delta.Length()) / 2.0f);

	// 速度の補正
	SimpleMath::Vector3 vn1 = rigidbody1->GetVelocity().Dot(direction) * direction;
	SimpleMath::Vector3 vn2 = rigidbody2->GetVelocity().Dot(direction) * direction;
	SimpleMath::Vector3 vt1 = rigidbody1->GetVelocity() - vn1;
	SimpleMath::Vector3 vt2 = rigidbody2->GetVelocity() - vn2;
	rigidbody1->SetVelocity(vn2 + vt1);
	rigidbody2->SetVelocity(vn1 + vt2);
}

/**
 * \brief ある点が三角形の内側にあるか.
 *
 * \param point 任意の点
 * \param triangle 三角形
 * \return
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

	// 内積の積が0以上なら法線の向きが揃っている
	if (dot0 * dot1 >= 0.0f &&
		dot1 * dot2 >= 0.0f &&
		dot2 * dot0 >= 0.0f) return true;
	else return false;
}


/**
 * 直線と平面の交点を求める.
 *
 * \param segment 線分
 * \param plane 平面
 * \return
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

	// 直線と平面の交点の距離
	float length = distance / dot;

	// 交点を求める
	SimpleMath::Vector3 intersection
		= segment->GetPos() + direction * length;

	return intersection;
}

DirectX::SimpleMath::Vector4 ConvertVector4(DirectX::SimpleMath::Vector3 v3)
{

	SimpleMath::Vector4 v4;

	v4.x = v3.x;
	v4.y = v3.y;
	v4.z = v3.z;
	v4.w = 1.0f;

	return v4;
}

DirectX::SimpleMath::Vector3 ConvertVector3(DirectX::SimpleMath::Vector4 v4)
{
	SimpleMath::Vector3 v3;

	v3.x = v4.x;
	v3.y = v4.y;
	v3.z = v4.z;

	return v3;
}
