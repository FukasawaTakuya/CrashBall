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
void SpriteRendererManager::Reder()
{
	m_spriteBatch->Begin();

	for (auto& renderCmd : m_renderCmd)
	{
		m_spriteBatch->Draw(
			renderCmd.pSprite,
			renderCmd.rect,
			renderCmd.color
		);
	}

	m_spriteBatch->End();
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
	const RECT rect, 
	const DirectX::XMVECTORF32 color)
{
	m_renderCmd.emplace_back(pSprite, rect, color);
}

void SpriteRendererManager::ClearRenderCmd()
{
	m_renderCmd.clear();
}

/**
 * \brief スプライトバッチの作成
 * 
 * \param context デバイスコンテキスト
 */
void SpriteRendererManager::CreateSpriteBatch(ID3D11DeviceContext1* context)
{
	m_spriteBatch = std::make_unique<SpriteBatch>(context);
}
