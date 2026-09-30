#include "pch.h"
#include "SoundManager.h"
#include "Game/Common/Utility.h"

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

	for (auto& file : std::filesystem::directory_iterator("Resources/Sound/BGM"))
	{
		// wstringに変換
		std::wstring path = Utility::ConvertToWideChar(file.path().string());

		// BGMの作成
		std::unique_ptr<SoundEffect> bgm
			= std::make_unique<SoundEffect>(audioEngine, path.c_str());

		// フォント名の抜き出し
		size_t end = path.rfind(L".");
		size_t start = path.rfind(L"BGM") + 4;
		std::wstring key = path.substr(start, end - start);
		// コンテナに追加
		m_bgmSounds.emplace(Utility::ConvertToMultiByteChar(key), std::move(bgm));
	}

	for (auto& file : std::filesystem::directory_iterator("Resources/Sound/SE"))
	{
		// wstringに変換
		std::wstring path = Utility::ConvertToWideChar(file.path().string());

		// SEの作成
		std::unique_ptr<SoundEffect> se
			= std::make_unique<SoundEffect>(audioEngine, path.c_str());

		// フォント名の抜き出し
		size_t end = path.rfind(L".");
		size_t start = path.rfind(L"SE") + 3;
		std::wstring key = path.substr(start, end - start);
		// コンテナに追加
		m_seSounds.emplace(Utility::ConvertToMultiByteChar(key), std::move(se));
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
