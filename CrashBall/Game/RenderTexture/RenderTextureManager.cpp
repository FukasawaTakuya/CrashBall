#include "pch.h"
#include "RenderTextureManager.h"

/**
 * \brief コンストラクタ
 * 
 */
RenderTextureMangaer::RenderTextureMangaer(DXGI_FORMAT format)
	: m_format(format)
{
}

/**
 * \brief レンダーテクスチャの作成
 * 
 * \param format
 */
MyRenderTexture* RenderTextureMangaer::CreateRenderTexture()
{
	auto renderTextrue = std::make_unique<MyRenderTexture>(m_format);
	renderTextrue->SetDevice(m_device);
	MyRenderTexture* ptr = renderTextrue.get();

	m_renderTextureList.push_back(std::move(renderTextrue));

	return ptr;
}

/**
 * \brief レンダーテクスチャの削除
 * 
 * \param renderTexture レンダーテクスチャ
 */
void RenderTextureMangaer::DeleteRenderTexture(MyRenderTexture* renderTexture)
{
	auto it = std::ranges::find_if(m_renderTextureList, [&](const std::unique_ptr<MyRenderTexture>& rt)
		{
			return rt.get() == renderTexture;
		}
	);

	if (it != m_renderTextureList.end())
	{
		m_renderTextureList.erase(it);
	}
}

/**
 * \brief CreateWindowSizeDependentResourcesで呼ぶ用
 * 
 * \param rect
 */
void RenderTextureMangaer::SetWindowSizeDependend(const RECT& rect)
{
	for (auto& renderTargetView : m_renderTextureList)
	{
		renderTargetView->SetWindowSizeDependend(rect);
	}
}
