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
#include "Game/Common/Utility.h"

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
 * \brief スプライトの生成
 * 
 * \param device デバイス
 */
void SpriteManager::CreateSprite(ID3D11Device1* device)
{
	m_spriteInfo.clear();

	for (auto& file : std::filesystem::directory_iterator("Resources/Sprite"))
	{
		// wstringに変換
		std::wstring path = Utility::ConvertToWideChar(file.path().string());

		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> sprite;

		// スプライトの作成
		DX::ThrowIfFailed(
			CreateDDSTextureFromFile(
				device,
				path.c_str(),
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

		// スプライト名を抜き出す
		size_t end = path.rfind(L".");
		size_t start = path.rfind(L"Sprite") + 7;
		std::wstring key = path.substr(start, end - start);
		// コンテナに追加
		m_spriteInfo.emplace(
			Utility::ConvertToMultiByteChar(key), 
			SpriteInfo(std::move(sprite), width, height));
	}
}

/**
 * \brief スプライト情報の取得
 * 
 * \param key キー
 * \return スプライト情報
 */
const SpriteInfo* SpriteManager::GetSpriteInfo(const std::string& key) const
{
	auto it = m_spriteInfo.find(key);

	if (it != m_spriteInfo.end())
	{
		return &it->second;
	}
	else return nullptr;
}
