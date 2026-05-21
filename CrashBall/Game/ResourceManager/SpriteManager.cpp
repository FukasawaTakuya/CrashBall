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
 * \brief ファクトリーに登録
 * 
 * \param key キー
 * \param fileName ファイル名
 */
void SpriteManager::RegisterFactory(std::string key, const wchar_t* fileName)
{
	m_factory.emplace(key, fileName);
}

/**
 * \brief スプライトの生成
 * 
 * \param device
 */
void SpriteManager::CreateSprite(ID3D11Device1* device)
{
	// コンテナのクリア
	m_sprites.clear();

	for (auto& file : m_factory)
	{
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;

		DX::ThrowIfFailed(
			CreateDDSTextureFromFile(
				device,
				file.second,
				nullptr,
				texture.ReleaseAndGetAddressOf()
			)
		);

		m_sprites.emplace(file.first, std::move(texture));
	}
}

/**
 * \brief スプライトの取得
 * 
 * \param key キー
 * \return スプライトのポインタ
 */
ID3D11ShaderResourceView* SpriteManager::GetSprite(const std::string& key)
{
	// キーから探す
	auto it = m_sprites.find(key);

	if (it != m_sprites.end())
	{
		return it->second.Get();
	}
	else return nullptr;
}
