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
	// 描画順にソート
	std::sort(m_renderCommad.begin(), m_renderCommad.end(),
		[](const SpriteRenderCommand& renderCommand1, const SpriteRenderCommand& renderCommand2)
		{
			return renderCommand1.orderInLayer < renderCommand2.orderInLayer;
		});

	m_spriteBatch->Begin();

	for (auto& renderCommand : m_renderCommad)
	{
		m_spriteBatch->Draw(
			renderCommand.pSprite,
			renderCommand.rect,
			renderCommand.color
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
	int orderInLayer,
	const DirectX::XMVECTORF32 color)
{
	m_renderCommad.emplace_back(pSprite, rect, orderInLayer, color);
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
