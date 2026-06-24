#include "pch.h"
#include "SpriteManager.h"
#include <DDSTextureLoader.h>
#include "Game/Component/Default/Renderer/SpriteRenderer.h"

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
 * \param device
 */
void SpriteManager::CreateSprite(ID3D11Device1* device)
{
	m_sprites.clear();

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
		SimpleMath::Vector2 size;
		ID3D11Resource* resource;
		sprite->GetResource(&resource);
		ID3D11Texture2D* texture = static_cast<ID3D11Texture2D*>(resource);
		D3D11_TEXTURE2D_DESC desc;
		texture->GetDesc(&desc);

		size.x = desc.Width;
		size.y = desc.Height;

		texture->Release();

		// コンテナに追加
		m_sprites.emplace(file.first, std::move(sprite));
		m_spriteSizes.emplace(file.first, size);
	}
}

/**
 * \brief スプライト描画コンポーネントのセットアップ
 * 
 * \param spriteRenderer スプライト描画コンポーネント
 */
void SpriteManager::SetUpSpriteRenderer(SpriteRenderer* spriteRenderer)
{
	const std::string& key = spriteRenderer->GetSpriteKey();

	auto it = m_sprites.find(key);

	if (it != m_sprites.end())
	{
		spriteRenderer->SetSprite(
			m_sprites[key].Get(),
			m_spriteSizes[key]
		);
	}
}

/**
 * \brief スプライトの取得
 * 
 * \param key キー
 * \return スプライト
 */
ID3D11ShaderResourceView* SpriteManager::GetSprite(const std::string& key)
{
	auto it = m_sprites.find(key);

	if (it != m_sprites.end())
	{
		return it->second.Get();
	}
	else return nullptr;
}
