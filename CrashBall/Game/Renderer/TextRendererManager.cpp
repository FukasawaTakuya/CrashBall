#include "pch.h"
#include "TextRendererManager.h"

using namespace DirectX;

TextRendererManager::TextRendererManager()
{
}

TextRendererManager::~TextRendererManager()
{
}

void TextRendererManager::Render(DirectX::SpriteBatch* spriteBatch)
{
	for (auto& renderCmd : m_renderCommad)
	{
		m_spriteFont->DrawString(
			spriteBatch,
			renderCmd.text.c_str(),
			renderCmd.position,
			renderCmd.color,
			0.0f,
			renderCmd.origin,
			renderCmd.scale,
			SpriteEffects_None,
			renderCmd.layerDepth
		);
	}
}

void TextRendererManager::RegisterRenderCommand(
	const DirectX::SimpleMath::Vector2& position, 
	const DirectX::XMVECTORF32& color, 
	float scale,
	const DirectX::SimpleMath::Vector2& origin,
	float layerDepth,
	const std::wstring& text)
{
	m_renderCommad.emplace_back(
		position,
		color,
		scale,
		origin,
		layerDepth,
		text
	);
}

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

