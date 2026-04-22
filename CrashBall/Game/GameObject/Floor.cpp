#include "pch.h"
#include "Floor.h"
#include "Game/ResourceManager/ResourceManager.h"

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
}

void MeshFloor::Rotate(DirectX::SimpleMath::Matrix rotate)
{
	m_transform->Rotate(rotate);
	m_collider->Rotate(rotate);
}
