#include "pch.h"
#include "ShadowMap.h"

void ShadowMap::Begin(ID3D11DeviceContext1* context)
{
    auto depthStencil = m_renderTexture->GetDepthStencilView();

    context->RSSetViewports(1, &m_viewport);

    float clearColor[] = { 0.0f, 0.0f, 0.0f, 0.0f };

    context->OMSetRenderTargets(
        1,
        nullptr,
        depthStencil);

    context->ClearRenderTargetView(
        nullptr,
        clearColor);

    context->ClearDepthStencilView(
        depthStencil,
        D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
        1.0f,
        0);
}
