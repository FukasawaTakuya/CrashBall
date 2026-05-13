#include "pch.h"
#include "Floor.h"
#include "Game/ResourceManager/ResourceManager.h"
#include "Game/Renderer/PrimitiveRendererManager.h"

using namespace DirectX;

MeshFloor::MeshFloor()
	: GameObject(ObjectTag::Stage)
{
	// コンポーネントの追加
	m_transform = AddComponent<Transform>();
	m_collider	= AddComponent<Mesh>();
	m_renderer	= AddComponent<ModelRenderer>();

	m_collider->SetLayerMask(LayerMask::Ground);

	m_collider->SetOnCollisionEnterCmd([this](Collider* other)
		{
			if (other->GetOwner()->GetTag() == ObjectTag::Player)
			{
				for(auto& hitface : m_collider->GetHitFace())
				{
					PaintFace(hitface, Colors::Blue);
				}
			}
			else if (other->GetOwner()->GetTag() == ObjectTag::Enemy)
			{
				for (auto& hitface : m_collider->GetHitFace())
				{
					PaintFace(hitface, Colors::Red);
				}
			}
		});
}

MeshFloor::~MeshFloor()
{
}

void MeshFloor::Initialize()
{
	// 拡大率の設定
	m_collider->SetScale(SCALE);

	// コライダーデータの読み込み
	m_collider->LoadObjData(L"Resources/Models/Stage2.obj");

	for (auto& face : m_collider->GetFace())
	{
		if (face->GetCenter().y >= 4.0f && face->GetCenter().y <= 8.0f)
		{
			m_stageMesh.push_back(face.get());
			m_faceColor.emplace(face.get(), Colors::White);
		}
		else {
			m_wallMesh.push_back(face.get());
		}
	}
}


void MeshFloor::Update()
{
}

void MeshFloor::Draw()
{
    auto primitiveRenderer = PrimitiveRendererManager::Instance;

	// 拡大行列
	SimpleMath::Matrix scale
		= SimpleMath::Matrix::CreateScale(SCALE);
	// 回転行列
	SimpleMath::Matrix rotate
		= SimpleMath::Matrix::CreateFromQuaternion(m_transform->GetQuaternion());
	// 移動行列
	SimpleMath::Matrix trans
		= SimpleMath::Matrix::CreateTranslation(m_transform->GetPosition());

	// ワールド行列
	SimpleMath::Matrix world = scale * rotate * trans;

	// 描画
    for (auto& face : m_collider->GetFace())
    {
		XMVECTORF32 faceColor = Colors::White;

		auto it = m_faceColor.find(face.get());
		if (it != m_faceColor.end())
		{
			faceColor = it->second;
		}

		// 頂点
		std::vector<DirectX::VertexPositionNormalColor> pos
		{
			VertexPositionNormalColor(face->GetPoint()[0], face->GetPlane()->GetNormal(), faceColor),
			VertexPositionNormalColor(face->GetPoint()[1], face->GetPlane()->GetNormal(), faceColor),
			VertexPositionNormalColor(face->GetPoint()[2], face->GetPlane()->GetNormal(), faceColor)
		};

		// 描画命令登録
		primitiveRenderer().RegisterDrawCommand({
            D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
            pos
            });
    }
}

void MeshFloor::Rotate(DirectX::SimpleMath::Matrix rotate)
{
	m_transform->Rotate(rotate);
	m_collider->Rotate(rotate);
}

/**
 * \brief 面に色を塗る
 * 
 * \param color
 */
void MeshFloor::PaintFace(Triangle* face, const XMVECTORF32& color)
{
	if (m_faceColor.find(face) != m_faceColor.end())
	{
		m_faceColor[face] = color;
	}
}
