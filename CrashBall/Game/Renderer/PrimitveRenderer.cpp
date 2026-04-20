#include "pch.h"
#include "PrimitveRenderer.h"
#include "Game/Common/CommonResources.h"


using namespace DirectX;

void PrimitiveManager::CreateResource(
	ID3D11Device1* device,
	ID3D11DeviceContext1* context,
    DirectX::SimpleMath::Matrix projMat
)
{
    m_primitiveBatch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(context);
    m_basicEffect = std::make_unique<BasicEffect>(device);

    m_basicEffect->SetProjection(projMat);
    m_basicEffect->SetVertexColorEnabled(true);

    DX::ThrowIfFailed(
        CreateInputLayoutFromEffect<VertexPositionColor>(
            device,
            m_basicEffect.get(),
            m_inputLayout.ReleaseAndGetAddressOf()));
}

void PrimitiveManager::ApplyEffect(Camera* camera)
{

    auto context = CommonResources::Instance().GetContext();

    m_basicEffect->SetProjection(camera->GetProjMat());
    m_basicEffect->SetView(camera->GetViewMat());
    m_basicEffect->SetWorld(SimpleMath::Matrix::Identity);

    m_basicEffect->Apply(context);
    context->IASetInputLayout(m_inputLayout.Get());
}

void PrimitiveManager::DrawLine(
    DirectX::VertexPositionColor v1,
    DirectX::VertexPositionColor v2)
{
    m_primitiveBatch->DrawLine(v1, v2);
}
