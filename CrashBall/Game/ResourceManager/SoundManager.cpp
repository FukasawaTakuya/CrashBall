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
 * \brief ファクトリーに登録
 * 
 * \param key
 * \param fileName
 */
void SoundManager::RegisterFactory(
	const std::string& key, 
	const wchar_t* fileName)
{
	m_bgmfactory.emplace(key, fileName);
}

/**
 * \brief サウンドの生成
 * 
 * \param audioEngine オーディオエンジン
 */
void SoundManager::CreateSound(DirectX::AudioEngine* audioEngine)
{
	for (auto& file : m_bgmfactory)
	{
		m_bgmSounds.emplace(
			file.first,
			std::make_unique<SoundEffect>(
				audioEngine,
				file.second
			)
		);
	}

	for (auto& file : m_sefactory)
	{
		m_seSounds.emplace(
			file.first,
			std::make_unique<SoundEffect>(
				audioEngine,
				file.second
			)
		);
	}
}

/**
 * \brief BGMの取得
 * 
 * \param key キー
 * \return サウンドエフェクトのポインタ
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
 * \return サウンドエフェクトのポインタ
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
