/*****************************************************************//**
 * \file   TextRendererManager.cpp
 * \brief  テキスト描画管理クラス
 *
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#include "pch.h"
#include "TextRendererManager.h"

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
	for (auto& renderCommand : m_renderCommad)
	{
		m_spriteFont->DrawString(
			spriteBatch,
			renderCommand.text.c_str(),
			renderCommand.position,
			renderCommand.color,
			renderCommand.rotate,
			renderCommand.origin,
			renderCommand.scale,
			SpriteEffects_None,
			renderCommand.layerDepth
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
	const DirectX::SimpleMath::Vector2& position,
	const DirectX::XMVECTORF32& color,
	float rotate,
	float scale,
	const DirectX::SimpleMath::Vector2& origin,
	float layerDepth,
	const std::wstring& text)
{
	m_renderCommad.emplace_back(
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
}

void TextRendererManager::Create(
	ID3D11Device1* device, 
	ID3D11DeviceContext1* context)
{
	m_spriteFont = std::make_unique<SpriteFont>(device, L"Resources/SpriteFont/myfont.spritefont");
	m_spriteBatch = std::make_unique<SpriteBatch>(context);
}

