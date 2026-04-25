#include "pch.h"
#include "Floor.h"
#include "Game/ResourceManager/ResourceManager.h"
#include "Game/Renderer/PrimitveRendererManager.h"

using namespace DirectX;

MeshFloor::MeshFloor()
{
	// コンポーネントの追加
	m_transform = AddComponent<Transform>();
	m_collider	= AddComponent<Mesh>();
	m_renderer	= AddComponent<ModelRenderer>();
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
}

void MeshFloor::Update(float elapsedTime)
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
	m_renderer->Draw(world);

    //for (auto& face : m_collider->GetFace())
    //{
    //    std::vector<DirectX::VertexPositionNormalColor> pos;
    //    pos.emplace_back(face->GetPoint()[0], Colors::Black);
    //    pos.emplace_back(face->GetPoint()[1], Colors::Black);
    //    pos.emplace_back(face->GetPoint()[2], Colors::Black);

    //    primitiveRenderer().RegisterDrawCommand({
    //        D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP,
    //        pos, 3
    //        });

    //    pos[0].color = SimpleMath::Vector4{ 0.9f, 0.9f, 0.9f, 0.95f };
    //    pos[1].color = SimpleMath::Vector4{ 0.9f, 0.9f, 0.9f, 0.95f };
    //    pos[2].color = SimpleMath::Vector4{ 0.9f, 0.9f, 0.9f, 0.95f };

    //    primitiveRenderer().RegisterDrawCommand({
    //        D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
    //        pos, 3
    //        });
    //}
}

void MeshFloor::Rotate(DirectX::SimpleMath::Matrix rotate)
{
	m_transform->Rotate(rotate);
	m_collider->Rotate(rotate);
}
