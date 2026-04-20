#include "pch.h"
#include "Floor.h"
#include "Game/Common/CommonResources.h"

using namespace DirectX;

MeshFloor::MeshFloor()
	: m_pModel{}
	, m_mesh{ std::make_unique<Mesh>() }
{
}

MeshFloor::~MeshFloor()
{
}

void MeshFloor::Initialize()
{
	m_mesh.get()->LoadObjData(L"Resources/Models/Stage.obj");
}

void MeshFloor::Update(float elapsedTime)
{
}

void MeshFloor::Draw(DirectX::SimpleMath::Matrix proj, DirectX::SimpleMath::Matrix view)
{
	auto context = CommonResources::Instance().GetContext();
	auto state = CommonResources::Instance().GetState();

	auto scale = SimpleMath::Matrix::CreateScale(0.99f);
	auto trans = SimpleMath::Matrix::CreateTranslation(SimpleMath::Vector3::Down) * 0.5f;
	auto rotate = SimpleMath::Matrix::CreateRotationY(XMConvertToRadians(0));
	trans = SimpleMath::Matrix::Identity;

	SimpleMath::Matrix world = m_rotate;

	m_pModel->Draw(context, *state, world, view, proj);
}

void MeshFloor::Rotate(DirectX::SimpleMath::Matrix rotate)
{
	m_rotate *= rotate;
	m_mesh->Rotate(rotate);
}
