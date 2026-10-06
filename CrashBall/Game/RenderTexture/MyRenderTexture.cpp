/*****************************************************************//**
 * \file   MyRenderTexture.cpp
 * \brief  レンダーテキスチャ生成クラス
 *
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#include "pch.h"
#include "MyRenderTexture.h"
#include "Game/Common/Screen.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 */
MyRenderTexture::MyRenderTexture(DXGI_FORMAT format)
    : m_renderTexture(std::make_unique<DX::RenderTexture>(format))
{
}

/**
 * \brief 描画開始
 * 
 * \param context コンテキスト
 */
void MyRenderTexture::Begin(ID3D11DeviceContext1* context)
{
    auto renderTargetView = m_renderTexture->GetRenderTargetView();
    auto depthStencil     = m_renderTexture->GetDepthStencilView();

    context->RSSetViewports(1, &m_viewport);
    context->OMSetRenderTargets(1, &renderTargetView, depthStencil);

    float clearColor[] = { 0.0f, 0.0f, 0.0f, 0.0f };

    context->ClearRenderTargetView(
        renderTargetView,
        clearColor
    );

    context->ClearDepthStencilView(
        depthStencil,
        D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
        1.0f,
        0
    );

    SimpleMath::Matrix view = m_camera->GetView();
    SimpleMath::Matrix proj = m_camera->GetProj();


    context->OMSetRenderTargets(
        1,
        &renderTargetView,
        depthStencil
    );
}

/**
 * \brief 描画終了
 * 
 * \param context デバイスコンテキスト
 * \param dsv 深度ステンシルビュー
 * \param backRtv バックレンダーターゲット
 */
void MyRenderTexture::End(
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

/**
 * \brief CreateWindowSizeDependentResourcesで呼ぶ用
 * 
 * \param rect
 */
void MyRenderTexture::SetWindowSizeDependend(const RECT& rect)
{
    if (m_isWindow)
    {
        SetWindow(rect);
    }
    else
    {
        SizeResources(m_width, m_height);
    }
}

// ====================== RenderTextureのラッパー ======================= //

void MyRenderTexture::SetDevice(ID3D11Device* device)
{
    m_renderTexture->SetDevice(device);
}

void MyRenderTexture::SizeResources(size_t width, size_t height)
{
    m_width  = width;
    m_height = height;

    m_renderTexture->SizeResources(m_width, m_height);

    m_viewport.TopLeftX = 0.0f;
    m_viewport.TopLeftY = 0.0f;
    m_viewport.Width    = m_width;
    m_viewport.Height   = m_height;
    m_viewport.MinDepth = 0.0f;
    m_viewport.MaxDepth = 1.0f;

    m_isWindow = false;
}

void MyRenderTexture::ReleaseDevice()
{
    m_renderTexture->ReleaseDevice();
}

void MyRenderTexture::SetWindow(const RECT& rect)
{
    m_renderTexture->SetWindow(rect);

    m_viewport.TopLeftX = 0.0f;
    m_viewport.TopLeftY = 0.0f;
    m_viewport.Width    = rect.right;
    m_viewport.Height   = rect.bottom;
    m_viewport.MinDepth = 0.0f;
    m_viewport.MaxDepth = 1.0f;

    m_isWindow = true;
}
