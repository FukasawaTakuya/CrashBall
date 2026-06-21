/*****************************************************************//**
 * \file   TextRendererManager.cpp
 * \brief  テキスト描画管理クラス
 *
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#include "pch.h"
#include "TextRendererManager.h"
#include "Game/Common/Screen.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 */
TextRendererManager::TextRendererManager()
{
}

/**
 * \brief デストラクタ
 * 
 */
TextRendererManager::~TextRendererManager()
{
}


/**
 * \brief 描画
 * 
 * \param spriteBatch スプライトバッチ
 */
void TextRendererManager::Render(DirectX::SpriteBatch* spriteBatch)
{
	// テキスト描画
	for (auto& renderCommand : m_renderCommad)
	{
		renderCommand.pSpriteFont->DrawString(
			spriteBatch,
			renderCommand.text.c_str(),
			renderCommand.position * Screen::GetScreenRate(),
			renderCommand.color,
			renderCommand.rotate,
			renderCommand.origin,
			renderCommand.scale * Screen::GetScreenRate(),
			SpriteEffects_None,
			renderCommand.layerDepth
		);
	}

	// デバッグ描画
	for (auto& debugRenderCommand : m_debugRenderCommad)
	{
		debugRenderCommand.pSpriteFont->DrawString(
			spriteBatch,
			debugRenderCommand.text.c_str(),
			debugRenderCommand.position * Screen::GetScreenRate(),
			debugRenderCommand.color,
			debugRenderCommand.rotate,
			debugRenderCommand.origin,
			debugRenderCommand.scale * Screen::GetScreenRate(),
			SpriteEffects_None,
			debugRenderCommand.layerDepth
		);
	}
}

/**
 * \brief 描画命令の登録
 * 
 * \param position 描画位置
 * \param color 色
 * \param rotate 回転
 * \param scale スケール
 * \param origin 基準位置
 * \param layerDepth 描画順
 * \param text テキスト
 */
void TextRendererManager::RegisterRenderCommand(
	DirectX::SpriteFont* pSpriteFont,
	const DirectX::SimpleMath::Vector2& position,
	const DirectX::XMVECTORF32& color,
	float rotate,
	float scale,
	const DirectX::SimpleMath::Vector2& origin,
	float layerDepth,
	const std::wstring& text)
{
	m_renderCommad.emplace_back(
		pSpriteFont,
		position,
		color,
		rotate,
		scale,
		origin,
		layerDepth,
		text
	);
}

void TextRendererManager::DebugRender(
	const DirectX::SimpleMath::Vector2& position, 
	const DirectX::XMVECTORF32& color, 
	float rotate, float scale, 
	const DirectX::SimpleMath::Vector2& origin, 
	float layerDepth, 
	const std::wstring& text)
{
	m_debugRenderCommad.emplace_back(
		m_debugFont.get(),
		position,
		color,
		rotate,
		scale,
		origin,
		layerDepth,
		text
	);
}

/**
 * \brief 描画命令のクリア
 * 
 */
void TextRendererManager::ClearnRenderCommand()
{
	m_renderCommad.clear();
	m_debugRenderCommad.clear();
}

void TextRendererManager::Create(
	ID3D11Device1* device, 
	ID3D11DeviceContext1* context)
{
	m_debugFont = std::make_unique<SpriteFont>(device, L"Resources/SpriteFont/myfont.spritefont");
	m_spriteBatch = std::make_unique<SpriteBatch>(context);
}

