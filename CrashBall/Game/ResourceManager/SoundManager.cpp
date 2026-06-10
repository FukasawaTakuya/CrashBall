#include "pch.h"
#include "SoundManager.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 */
SoundManager::SoundManager()
{
}

/**
 * \brief デストラクタ
 * 
 */
SoundManager::~SoundManager()
{
}

/**
 * \brief BGMのファイル名を登録
 * 
 * \param key キー
 * \param fileName ファイル名
 */
void SoundManager::RegisterBgmFile(
	const std::string& key, 
	const std::wstring& fileName)
{
	m_bgmfile.emplace(key, fileName);
}

/**
 * \brief SEのファイル名を登録
 *
 * \param key キー
 * \param fileName ファイル名
 */
void SoundManager::RegisterSeFile(
	const std::string& key,
	const std::wstring& fileName)
{
	m_sefile.emplace(key, fileName);
}

/**
 * \brief サウンドの生成
 * 
 * \param audioEngine オーディオエンジン
 */
void SoundManager::CreateSound(DirectX::AudioEngine* audioEngine)
{
	for (auto& file : m_bgmfile)
	{
		// BGMの作成
		std::unique_ptr<SoundEffect> bgm 
			= std::make_unique<SoundEffect>(audioEngine, file.second.c_str());
		// コンテナに追加
		m_bgmSounds.emplace(file.first, std::move(bgm));
	}

	for (auto& file : m_sefile)
	{
		// SEの作成
		std::unique_ptr<SoundEffect> se
			= std::make_unique<SoundEffect>(audioEngine, file.second.c_str());
		// コンテナに追加
		m_seSounds.emplace(file.first, std::move(se));
	}
}

/**
 * \brief BGMの取得
 * 
 * \param key キー
 * \return サウンドエフェクト
 */
DirectX::SoundEffect* SoundManager::GetBgmSound(const std::string key)
{
	auto it = m_bgmSounds.find(key);
	// イテレータが終端でなければ
	if (it != m_bgmSounds.end())
	{
		return it->second.get();
	}
	else return nullptr;
}

/**
 * \brief SEの取得
 * 
 * \param key キー
 * \return サウンドエフェクト
 */
DirectX::SoundEffect* SoundManager::GetSeSound(const std::string key)
{
	auto it = m_seSounds.find(key);
	// イテレータが終端でなければ
	if (it != m_seSounds.end())
	{
		return it->second.get();
	}
	else return nullptr;

}
