#include "pch.h"
#include "SpriteRendererManager.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 */
SpriteRendererManager::SpriteRendererManager()
{
}

/**
 * \brief デストラクタ
 * 
 */
SpriteRendererManager::~SpriteRendererManager()
{
}

/**
 * \brief 描画
 * 
 */
void SpriteRendererManager::Render(DirectX::SpriteBatch* spriteBatch)
{
	for (auto& renderCommand : m_renderCommad)
	{
		if (renderCommand.pSprite == nullptr) continue;

		spriteBatch->Draw(
			renderCommand.pSprite,
			renderCommand.position,
			nullptr,
			renderCommand.color,
			0.0f,
			renderCommand.origin,
			1.0f,
			SpriteEffects_None,
			renderCommand.layerDepth
		);
	}
}

/**
 * \brief 描画命令の登録
 *
 * \param pSprite スプライトのポインタ
 * \param rect 描画範囲
 * \param color 色
 */
void SpriteRendererManager::RegisterRenderCommand(
	ID3D11ShaderResourceView* pSprite,
	const DirectX::SimpleMath::Vector2& position,
	const DirectX::SimpleMath::Vector2& origin,
	float layerDepth,
	const DirectX::XMVECTORF32 color)
{
	m_renderCommad.emplace_back(pSprite, position, origin, layerDepth, color);
}

void SpriteRendererManager::ClearRenderCommand()
{
	m_renderCommad.clear();
}

/**
 * \brief スプライトバッチの作成
 * 
 * \param context デバイスコンテキスト
 */
void SpriteRendererManager::Create(ID3D11DeviceContext1* context)
{
	m_spriteBatch = std::make_unique<SpriteBatch>(context);
}
