#include "pch.h"
#include "RenderTexture.h"
#include "Game/Common/Screen.h"

RenderTexture::RenderTexture()
{
}

void RenderTexture::Create(DX::DeviceResources* deviceResources)
{
    RECT rc;
    GetClientRect(deviceResources->GetWindow(), &rc);

    D3D11_TEXTURE2D_DESC texDesc{};
    texDesc.Width = rc.right;
    texDesc.Height = rc.bottom;
    texDesc.MipLevels = 1;
    texDesc.ArraySize = 1;
    texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    texDesc.SampleDesc.Count = 1;
    texDesc.Usage = D3D11_USAGE_DEFAULT;
    texDesc.BindFlags =
        D3D11_BIND_RENDER_TARGET |
        D3D11_BIND_SHADER_RESOURCE;

    auto device = deviceResources->GetD3DDevice();

    device->CreateTexture2D(
        &texDesc,
        nullptr,
        m_texture.ReleaseAndGetAddressOf()
    );

    device->CreateRenderTargetView(
        m_texture.Get(),
        nullptr,
        m_rtv.ReleaseAndGetAddressOf()
    );

    device->CreateShaderResourceView(
        m_texture.Get(),
        nullptr,
        m_srv.ReleaseAndGetAddressOf()
    );
}

void RenderTexture::Begin(
    ID3D11DeviceContext1* context,
    ID3D11DepthStencilView* dsv)
{
    ID3D11RenderTargetView* rtv = m_rtv.Get();
    context->OMSetRenderTargets(
        1,
        &rtv,
        dsv
    );

    float clearColor[4] =
    {
        0.2f,
        0.2f,
        0.2f,
        1.0f
    };

    context->ClearRenderTargetView(
        m_rtv.Get(),
        clearColor
    );
}

void RenderTexture::End(
    ID3D11DeviceContext1* context,
    ID3D11DepthStencilView* dsv,
    ID3D11RenderTargetView* const backRtv)
{
    context->OMSetRenderTargets(
        1,
        &backRtv,
        dsv
    );
}
