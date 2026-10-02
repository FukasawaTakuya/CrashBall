/*****************************************************************//**
 * \file   RenderTexture.cpp
 * \brief  レンダーテキスチャ生成クラス
 *
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#include "pch.h"
#include "MyRenderTexture.h"
#include "Game/Common/Screen.h"

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
 * \param dsv 深度ステンシルビュー
 */
void MyRenderTexture::Begin(
    ID3D11DeviceContext1* context,
    ID3D11DepthStencilView* dsv)
{
    ID3D11RenderTargetView* rtv = m_renderTexture->GetRenderTargetView();
    context->OMSetRenderTargets(
        1,
        &rtv,
        dsv
    );

    // 塗りつぶしの色
    float clearColor[4] =
    {
        0.2f,
        0.2f,
        0.2f,
        1.0f
    };

    context->ClearRenderTargetView(
        rtv,
        clearColor
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

// ====================== RenderTextureのラッパー ======================= //

void MyRenderTexture::SetDevice(ID3D11Device* device)
{
    m_renderTexture->SetDevice(device);
}

void MyRenderTexture::SizeResources(size_t width, size_t height)
{
    m_renderTexture->SizeResources(width, height);

    m_viewport.TopLeftX = 0.0f;
    m_viewport.TopLeftY = 0.0f;
    m_viewport.Width    = width;
    m_viewport.Height   = height;
    m_viewport.MinDepth = 0.0f;
    m_viewport.MaxDepth = 1.0f;
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

}
