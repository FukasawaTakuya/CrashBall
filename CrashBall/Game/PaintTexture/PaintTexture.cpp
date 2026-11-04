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
		m_renderTexture->GetRenderTargetView(),
		clearColor);

	m_paintCommands.clear();
}

/**
 * \brief 描画
 * 
 * \param spriteBatch
 * \param states
 */
void PaintTexture::Draw(
	DirectX::SpriteBatch* spriteBatch,
	DirectX::CommonStates* states)
{
	auto renderTargetView = m_renderTexture->GetRenderTargetView();

	// レンダーターゲットの設定
    m_context->OMSetRenderTargets(1, &renderTargetView, nullptr);
	// ビューポートの設定
	m_context->RSSetViewports(1, &m_viewport);

	// 描画領域
	RECT inkRect(0, 0, m_inkSpriteWidth, m_inkSpriteHeight);

	spriteBatch->Begin(SpriteSortMode_Deferred);

	for (auto& paintCommand : m_paintCommands)
	{
		spriteBatch->Draw(
			m_inkSprite,
			paintCommand.position * m_width,
			&inkRect,
			paintCommand.color,
			0.0f,
			SimpleMath::Vector2(m_inkSpriteWidth / 2.0f, m_inkSpriteHeight / 2.0f),
			SimpleMath::Vector2(0.02f, 0.02f));
	}

	spriteBatch->End();

	m_paintCommands.clear();
}
