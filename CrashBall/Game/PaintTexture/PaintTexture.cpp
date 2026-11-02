/*****************************************************************//**
 * \file   PaintTexture.cpp
 * \brief  ペイントテクスチャ
 *
 * \author 深沢拓矢
 * \date   November 2026
 *********************************************************************/

#include "pch.h"
#include "PaintTexture.h"

using namespace DirectX;

/**
 * \brief ペイントテクスチャ
 * 
 * \param format
 */
PaintTexture::PaintTexture(DXGI_FORMAT format)
	: MyRenderTexture(format)
{
}

/**
 * \brief 描画命令の登録
 * 
 * \param position 描画位置
 * \param color 色
 */
void PaintTexture::RegisterRenderCommnad(
	const DirectX::SimpleMath::Vector2& position, 
	const DirectX::SimpleMath::Color& color)
{
	m_paintCommands.emplace_back(position, color);
}

bool init = false;

void PaintTexture::Draw(ID3D11DeviceContext1* context, DirectX::SpriteBatch* spriteBatch)
{
	auto renderTargetView = m_renderTexture->GetRenderTargetView();

	context->RSSetViewports(1, &m_viewport);
    context->OMSetRenderTargets(1, &renderTargetView, nullptr);

	spriteBatch->Begin();

	RECT inkRect(0, 0, m_inkSpriteWidth, m_inkSpriteHeight);
	for (auto& paintCommand : m_paintCommands)
	{
		auto pos = paintCommand.position * 4096.0f;
		spriteBatch->Draw(
			m_inkSprite,
			paintCommand.position * 4096.0f,
			&inkRect,
			paintCommand.color,
			0.0f,
			SimpleMath::Vector2(200.0f, 200.0f),
			SimpleMath::Vector2(0.025f, 0.025f));
	}

	spriteBatch->End();

	m_paintCommands.clear();

	context->OMSetRenderTargets(
		0,
		nullptr,
		nullptr);
}
