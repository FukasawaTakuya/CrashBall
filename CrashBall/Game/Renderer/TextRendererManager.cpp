#include "pch.h"
#include "TextRendererManager.h"

using namespace DirectX;

TextRendererManager::TextRendererManager()
{
}

TextRendererManager::~TextRendererManager()
{
}

void TextRendererManager::Render()
{
	m_spriteBatch->Begin();

	for (auto& renderCmd : m_renderCommad)
	{
		m_spriteFont->DrawString(
			m_spriteBatch.get(),
			renderCmd.text.c_str(),
			renderCmd.position,
			renderCmd.color,
			0.0f,
			SimpleMath::Vector3::Zero,
			renderCmd.scale
		);
	}

	m_spriteBatch->End();
}

void TextRendererManager::RegisterRenderCommand(
	DirectX::SimpleMath::Vector2 position, 
	DirectX::XMVECTORF32 color, 
	float scale, 
	const std::wstring& text)
{
	m_renderCommad.emplace_back(
		position,
		color,
		scale,
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

