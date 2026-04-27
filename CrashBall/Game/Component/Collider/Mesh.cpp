#include "pch.h"
#include "Mesh.h"

#include <fstream>
#include <sstream>
#include <string>
#include "Game/CollisionManager/Collision.h"

Mesh::Mesh()
	: Collider(ColliderType::Mesh)
{
}

bool Mesh::OnCollide(Collider* collider)
{
	return collider->OnCollideWith(this);
}


bool Mesh::OnCollideWith(Sphere* sphere)
{
	return Collision::IsCollision(this, sphere);
}

bool Mesh::OnCollideWith(Mesh* mesh)
{
	return false;
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
			vertex.emplace_back(x * m_scale, y * m_scale, z * m_scale);
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

	return true;
}

void Mesh::Rotate(DirectX::SimpleMath::Matrix rotate)
{
	for (auto& face : m_faces) {
		face->Rotate(rotate, m_position);
	}
}
