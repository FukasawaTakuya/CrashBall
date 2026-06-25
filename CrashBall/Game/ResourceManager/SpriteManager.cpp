/*****************************************************************//**
 * \file   SpriteManager.cpp
 * \brief  スプライト管理クラス
 *
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#include "pch.h"
#include "SpriteManager.h"
#include <DDSTextureLoader.h>

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 */
SpriteManager::SpriteManager()
{
}

/**
 * \brief デストラクタ
 * 
 */
SpriteManager::~SpriteManager()
{
}

/**
 * \brief ファイル名を登録
 * 
 * \param key キー
 * \param fileName ファイル名
 */
void SpriteManager::RegisterFile(
	const std::string& key, 
	const std::wstring& fileName)
{
	m_files.emplace(key, fileName);
}

/**
 * \brief スプライトの生成
 * 
 * \param device デバイス
 */
void SpriteManager::CreateSprite(ID3D11Device1* device)
{
	m_spriteInfo.clear();

	for (auto& file : m_files)
	{
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> sprite;

		// スプライトの作成
		DX::ThrowIfFailed(
			CreateDDSTextureFromFile(
				device,
				file.second.c_str(),
				nullptr,
				sprite.ReleaseAndGetAddressOf()
			)
		);

		// スプライトのサイズを求める
		float width;
		float height;

		ID3D11Resource* resource;
		sprite->GetResource(&resource);
		ID3D11Texture2D* texture = static_cast<ID3D11Texture2D*>(resource);
		D3D11_TEXTURE2D_DESC desc;
		texture->GetDesc(&desc);

		width = desc.Width;
		height = desc.Height;

		texture->Release();

		// コンテナに追加
		m_spriteInfo.emplace(file.first, SpriteInfo(std::move(sprite), width, height));
	}
}

/**
 * \brief スプライト情報の取得
 * 
 * \param key キー
 * \return スプライト情報
 */
SpriteInfo* SpriteManager::GetSpriteInfo(const std::string& key)
{
	auto it = m_spriteInfo.find(key);

	if (it != m_spriteInfo.end())
	{
		return &it->second;
	}
	else return nullptr;
}
