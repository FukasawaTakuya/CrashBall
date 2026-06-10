#include "pch.h"
#include "SpriteRendererManager.h"
#include <Game/Common/Screen.h>

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
			renderCommand.position * Screen::GetScreenRate(),
			&renderCommand.srcRect,
			renderCommand.color,
			renderCommand.rotate,
			renderCommand.origin,
			renderCommand.scale * Screen::GetScreenRate(),
			SpriteEffects_None,
			renderCommand.layerDepth
		);
	}
}

/**
 * \brief 描画命令の登録
 * 
 * \param pSprite スプライト
 * \param position 描画位置
 * \param color 色
 * \param rotate 回転
 * \param scale スケール
 * \param origin 基準位置
 * \param layerDepth 描画順
 */
void SpriteRendererManager::RegisterRenderCommand(
	ID3D11ShaderResourceView* pSprite,
	const DirectX::SimpleMath::Vector2& position,
	const RECT& srcRect,
	const DirectX::XMVECTORF32& color,
	float rotate,
	float scale,
	const DirectX::SimpleMath::Vector2& origin,
	float layerDepth)
{
	RegisterRenderCommand(
		pSprite,
		position, 
		srcRect,
		color, 
		rotate, 
		SimpleMath::Vector2(scale, scale), 
		origin, 
		layerDepth);
}

/**
 * \brief 描画命令の登録
 *
 * \param pSprite スプライト
 * \param position 描画位置
 * \param color 色
 * \param rotate 回転
 * \param scale スケール
 * \param origin 基準位置
 * \param layerDepth 描画順
 */
void SpriteRendererManager::RegisterRenderCommand(
	ID3D11ShaderResourceView* pSprite, 
	const DirectX::SimpleMath::Vector2& position,
	const RECT& srcRect,
	const DirectX::XMVECTORF32& color, 
	float rotate, 
	const DirectX::SimpleMath::Vector2& scale, 
	const DirectX::SimpleMath::Vector2& origin, 
	float layerDepth)
{
	m_renderCommad.emplace_back(
		pSprite, 
		position,
		srcRect,
		color, 
		rotate, 
		scale, 
		origin, 
		layerDepth);
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
