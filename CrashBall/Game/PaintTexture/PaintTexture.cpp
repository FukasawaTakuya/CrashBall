/*****************************************************************//**
 * \file   PaintTexture.cpp
 * \brief  ペイントテクスチャ
 *
 * \author 深沢拓矢
 * \date   November 2026
 *********************************************************************/

#include "pch.h"
#include "PaintTexture.h"

#include "Game/Framework/Time.h"

using namespace DirectX;

/**
 * \brief ペイントテクスチャ
 * 
 * \param format
 */
PaintTexture::PaintTexture(RenderTextureMangaer* renderTextureManager)
	:  m_pixelShader(std::make_unique<Shader>())
{
	m_paintTexture = renderTextureManager->CreateCustomRenderTexture(DXGI_FORMAT_B8G8R8A8_UNORM, false);
	m_paintTimeTex = renderTextureManager->CreateCustomRenderTexture(DXGI_FORMAT_R16G16_UINT, false);
	m_paintTimeTex->SizeResources(TEXTURE_SIZE, TEXTURE_SIZE);
	m_paintTexture->SizeResources(TEXTURE_SIZE, TEXTURE_SIZE);
}

/**
 * \brief 描画命令の登録
 * 
 * \param position 描画位置
 * \param color 色
 */
void PaintTexture::RegisterRenderCommnad(
	const DirectX::SimpleMath::Vector2& position, 
	const DirectX::SimpleMath::Color& color,
	int id)
{
	m_paintCommands.emplace_back(position, color, id);
}

/**
 * \brief ペイントのクリア
 * 
 */
void PaintTexture::ClearPaint()
{
	float clearColor[]
	{
		0.0f, 0.0f, 0.0f, 0.0f
	};

	m_context->ClearRenderTargetView(
		m_paintTexture->GetRenderTargetView(),
		clearColor);

	m_context->ClearRenderTargetView(
		m_paintTimeTex->GetRenderTargetView(),
		clearColor);

	m_paintCommands.clear();
}

/**
 * \brief 描画
 * 
 * \param spriteBatch スプライトバッチ
 * \param states コモンステート
 */
void PaintTexture::Draw(
	DirectX::SpriteBatch* spriteBatch,
	DirectX::CommonStates* states)
{
	ID3D11RenderTargetView* renderTargetView[]
		= { m_paintTexture->GetRenderTargetView(),
			m_paintTimeTex->GetRenderTargetView(), };

	// レンダーターゲットの設定
	m_context->OMSetRenderTargets(2, renderTargetView, nullptr);
	// ビューポートの設定
	auto viewPort = m_paintTexture->GetViewPort();
	m_context->RSSetViewports(1, &viewPort);

	// 描画領域
	RECT inkRect(0, 0, m_inkSpriteWidth, m_inkSpriteHeight);

	// フレーム数
	m_pixelShader->GetConstatntBufferInfo("TimeTexInfo")->SetVariable("time", Time::GetFrameCount());

	// 描画
	spriteBatch->Begin(
		SpriteSortMode_Immediate,
		m_paintBlendState.Get(),
		nullptr,
		nullptr,
		nullptr,
		[&]()
		{
			m_pixelShader->Bind(m_context);
		});

	for (auto& paintCommand : m_paintCommands)
	{
		m_pixelShader->GetConstatntBufferInfo("TimeTexInfo")->SetVariable("id", paintCommand.id);
		m_pixelShader->UpdateSubResources(m_context);

		spriteBatch->Draw(
			m_inkSprite,
			paintCommand.position * m_paintTexture->GetWidth(),
			&inkRect,
			paintCommand.color,
			0.0f,
			SimpleMath::Vector2(m_inkSpriteWidth / 2.0f, m_inkSpriteHeight / 2.0f),
			INKSPRITE_SCALE);
	}

	spriteBatch->End();

	m_paintCommands.clear();
}

/**
 * \brief ブレンドステートの作成
 * 
 * \param states コモンステート
 * \param device デバイス
 */
void PaintTexture::CreateBlendState(
	DirectX::CommonStates* states,
	ID3D11Device1* device)
{
	D3D11_BLEND_DESC blendDesc;

	states->AlphaBlend()->GetDesc(&blendDesc);

	blendDesc.IndependentBlendEnable = TRUE;

	blendDesc.RenderTarget[1].BlendEnable = FALSE;
	blendDesc.RenderTarget[1].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	device->CreateBlendState(&blendDesc, m_paintBlendState.ReleaseAndGetAddressOf());
}

