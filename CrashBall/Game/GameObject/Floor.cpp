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

	m_collider->SetLayerMask(LayerMask::Ground);
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
	//m_renderer->Draw(world);

    for (auto& face : m_collider->GetFace())
    {
		// 頂点
		std::vector<DirectX::VertexPositionNormalColor> pos
		{
			VertexPositionNormalColor(face->GetPoint()[0], face->GetPlane()->GetNormal(), Colors::White),
			VertexPositionNormalColor(face->GetPoint()[1], face->GetPlane()->GetNormal(), Colors::White),
			VertexPositionNormalColor(face->GetPoint()[2], face->GetPlane()->GetNormal(), Colors::White)
		};

		// 描画命令登録
		primitiveRenderer().RegisterDrawCommand({
            D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
            pos
            });

		// 色変更
		pos[0].color = SimpleMath::Vector4{ 0.0f, 0.0f, 0.0f, 1.0f };
		pos[1].color = SimpleMath::Vector4{ 0.0f, 0.0f, 0.0f, 1.0f };
		pos[2].color = SimpleMath::Vector4{ 0.0f, 0.0f, 0.0f, 1.0f };

		// 線用の頂点を法線方向にずらす
		pos[0].position = pos[0].position + face->GetPlane()->GetNormal() * 0.01f;
		pos[1].position = pos[1].position + face->GetPlane()->GetNormal() * 0.01f;
		pos[2].position = pos[2].position + face->GetPlane()->GetNormal() * 0.01f;

		// 描画命令登録
        //primitiveRenderer().RegisterDrawCommand({
        //    D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP,
        //    pos
        //    });
    }
}

void MeshFloor::Rotate(DirectX::SimpleMath::Matrix rotate)
{
	m_transform->Rotate(rotate);
	m_collider->Rotate(rotate);
}
