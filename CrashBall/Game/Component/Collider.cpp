#include <pch.h>
#include <fstream>
#include <sstream>
#include <string>

#include "Collider.h"

using namespace DirectX;

Sphere::Sphere(DirectX::SimpleMath::Vector3 pos, float radius)
	: m_pos{ pos }
	, m_radius{ radius }
{
}

Plane::Plane()
{
}

void Plane::SetPlane(
	DirectX::SimpleMath::Vector3 normal,
	DirectX::SimpleMath::Vector3 point)
{
	m_vec4.x = normal.x;
	m_vec4.y = normal.y;
	m_vec4.z = normal.z;
	m_point = point;

	m_vec4.w = -(m_vec4.x * m_point.x + m_vec4.y * m_point.y + m_vec4.z * m_point.z);
}

void Plane::SetPlane(
	DirectX::SimpleMath::Vector3 point1,
	DirectX::SimpleMath::Vector3 point2,
	DirectX::SimpleMath::Vector3 point3)
{
	SimpleMath::Vector3 vec1 = point2 - point1;
	SimpleMath::Vector3 vec2 = point3 - point2;

	SimpleMath::Vector3 normal = vec1.Cross(vec2);

	normal.Normalize();

	SetPlane(normal, point1);
}

void Plane::Rotate(DirectX::SimpleMath::Matrix rotate)
{
	// 平面情報の再定義
	DirectX::SimpleMath::Vector4 newVec = DirectX::XMPlaneTransform(m_vec4, rotate);
	// 平面情報の正規化
	m_vec4 = DirectX::XMPlaneNormalize(newVec);

}

float Plane::CalcLength(DirectX::SimpleMath::Vector3 point)
{
	return std::abs(m_vec4.x * point.x + m_vec4.y * point.y + m_vec4.z * point.z + m_vec4.w);
}

DirectX::SimpleMath::Vector3 Plane::GetNormal()
{
	// 法線ベクトル
	DirectX::SimpleMath::Vector3 normal;
	normal.x = m_vec4.x;
	normal.y = m_vec4.y;
	normal.z = m_vec4.z;

	normal.Normalize();

	return normal;
}

DirectX::SimpleMath::Vector3 Plane::GetSlope()
{
	// 重力の方向
	DirectX::SimpleMath::Vector3 v = DirectX::SimpleMath::Vector3::Down;
	// 法線ベクトル
	DirectX::SimpleMath::Vector3 normal = GetNormal();

	// 法線方向の成分
	float sub = v.Dot(normal);

	// 法線方向のベクトルを引く
	DirectX::SimpleMath::Vector3 slope = v - sub * normal;

	// 正規化
	slope.Normalize();

	return slope;

}

void Triangle::SetTriangle(
	DirectX::SimpleMath::Vector3 point1,
	DirectX::SimpleMath::Vector3 point2,
	DirectX::SimpleMath::Vector3 point3)
{
	m_point[0] = point1;
	m_point[1] = point2;
	m_point[2] = point3;

	m_plane.SetPlane(point1, point2, point3);
}

void Triangle::Rotate(
	DirectX::SimpleMath::Matrix rotate,
	DirectX::SimpleMath::Vector3 center)
{
	for (auto& point : m_point) {
		SimpleMath::Matrix trans
			= SimpleMath::Matrix::CreateTranslation(center);

		SimpleMath::Matrix invert = SimpleMath::Matrix::CreateTranslation(-center);

		SimpleMath::Matrix world = trans * rotate * invert;

		point = XMVector3Transform(point, world);
	}
	m_plane.Rotate(rotate);
}


bool Mesh::LoadObjData(const wchar_t* filename)
{
	std::vector<SimpleMath::Vector3> vertex;

	std::ifstream ifs(filename);

	if (!ifs.is_open()) {
		OutputDebugString(L"File Open Error! : %s", filename);

		return false;
	}

	std::string line;

	while (std::getline(ifs, line)) {

		std::istringstream iss(line);
		std::string type;
		iss >> type;
		if (type == "v") {
			float x, y, z;
			iss >> x >> y >> z;
			z *= -1;
			vertex.emplace_back(x, y, z);
		}
		else if (type == "f") {
			std::vector<int> index;

			std::string item;
			for (int i = 0; i < 3; i++) {
				// 頂点情報だけ抜き取る
				getline(iss, item, '/');
				index.push_back(stoi(item));
				//getline(iss, item, '/');
				getline(iss, item, ' ');
			}
			// 残りの文字を確認
			getline(iss, item);
			if (item.size() >= 5) {
				std::istringstream ss(item);
				std::string num;
				getline(ss, num, '/');
				index.push_back(stoi(num));

				m_faces.push_back(std::make_unique<Triangle>());
				m_faces.back()->SetTriangle(vertex[index[0] - 1], vertex[index[3] - 1], vertex[index[2] - 1]);
				m_faces.push_back(std::make_unique<Triangle>());
				m_faces.back()->SetTriangle(vertex[index[0] - 1], vertex[index[2] - 1], vertex[index[1] - 1]);
			}
			else {
				m_faces.push_back(std::make_unique<Triangle>());
				m_faces.back()->SetTriangle(vertex[index[0] - 1], vertex[index[2] - 1], vertex[index[1] - 1]);
			}
		}

	}

	ifs.close();

	for (auto& face : m_faces) {
		for (int i = 0; i < 3; i++) {
			OutputDebugString(L"x:%f y:%f z:%f\n", 
				face.get()->GetPoint()[i].x, face.get()->GetPoint()[i].y, face.get()->GetPoint()[i].z);
		}
		OutputDebugString(L"\n");
	}

	OutputDebugString(L"%d\n", m_faces.size());

	return true;
}

//bool Mesh::IsCollision(Sphere* sphere)
//{
//	m_hitFace = nullptr;
//
//	for (auto& face : m_faces) {
//		if (Collision::IsCollision(sphere, face.get())) {
//			m_hitFace = face.get();
//			return true;
//		}
//	}
//	return false;
//}
//
//void Mesh::ResolveCol(Ball* ball)
//{
//	if (m_hitFace == nullptr) return;
//
//	Collision::ResolveCollision(ball, m_hitFace->GetPlane());
//}
//
//void Mesh::Rotate(DirectX::SimpleMath::Matrix rotate)
//{
//	for (auto& face : m_faces) {
//		face->Rotate(rotate, m_position);
//	}
//}
