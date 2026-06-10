/*****************************************************************//**
 * \file   TextManager.cpp
 * \brief  テキスト管理クラス
 *
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#include "pch.h"
#include "TextManager.h"

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
 * \brief ファイルの登録
 * 
 * \param key キー
 * \param fileName ファイル名
 */
void TextManager::RegisterFile(
	const std::string& key, 
	const std::wstring& fileName)
{
	m_files.emplace(key, fileName);
}

/**
 * \brief スプライトフォントの作成
 * 
 * \param device デバイス
 */
void TextManager::CreateSpriteFont(ID3D11Device1* device)
{
	m_spriteFonts.clear();

	for (auto& file : m_files)
	{
		std::unique_ptr<SpriteFont> spriteFont = std::make_unique<SpriteFont>(device, file.second.c_str());

		m_spriteFonts.emplace(file.first, std::move(spriteFont));
	}
}

/**
 * \brief スプライトフォントの取得
 * 
 * \param key キー
 * \return スプライトフォント
 */
DirectX::SpriteFont* TextManager::GetSpriteFont(const std::string& key)
{
	auto it = m_spriteFonts.find(key);

	if (it != m_spriteFonts.end())
	{
		return it->second.get();
	}
	else return nullptr;
}
