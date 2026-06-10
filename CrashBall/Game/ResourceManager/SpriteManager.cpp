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
 * \param device
 */
void SpriteManager::CreateSprite(ID3D11Device1* device)
{
	m_sprites.clear();

	for (auto& file : m_files)
	{
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;

		// スプライトの作成
		DX::ThrowIfFailed(
			CreateDDSTextureFromFile(
				device,
				file.second.c_str(),
				nullptr,
				texture.ReleaseAndGetAddressOf()
			)
		);

		// コンテナに追加
		m_sprites.emplace(file.first, std::move(texture));
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
