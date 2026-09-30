/*****************************************************************//**
 * \file   TextManager.cpp
 * \brief  テキスト管理クラス
 *
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#include "pch.h"
#include "TextManager.h"
#include "Game/Common/Utility.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 */
TextManager::TextManager()
{
}

/**
 * \brief デストラクタ
 * 
 */
TextManager::~TextManager()
{
}

/**
 * \brief スプライトフォントの作成
 * 
 * \param device デバイス
 */
void TextManager::CreateSpriteFont(ID3D11Device1* device)
{
	m_spriteFonts.clear();

	for (auto& file : std::filesystem::directory_iterator("Resources/SpriteFont"))
	{
		// wstringに変換
		std::wstring path = Utility::ConvertToWideChar(file.path().string());

		// フォントの作成
		std::unique_ptr<SpriteFont> spriteFont = std::make_unique<SpriteFont>(device, path.c_str());

		// フォント名の抜き出し
		size_t end = path.rfind(L".");
		size_t start = path.rfind(L"SpriteFont") + 11;
		std::wstring key = path.substr(start, end - start);
		// コンテナに追加
		m_spriteFonts.emplace(Utility::ConvertToMultiByteChar(key), std::move(spriteFont));
	}
}

/**
 * \brief スプライトフォントの取得
 * 
 * \param key キー
 * \return スプライトフォント
 */
DirectX::SpriteFont* TextManager::GetSpriteFont(const std::string& key) const
{
	auto it = m_spriteFonts.find(key);

	if (it != m_spriteFonts.end())
	{
		return it->second.get();
	}
	else return nullptr;
}
