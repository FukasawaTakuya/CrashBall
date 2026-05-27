/*****************************************************************//**
 * \file   SoundPlayer.cpp
 * \brief  サウンド再生クラス
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#include "pch.h"
#include "SoundPlayer.h"

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 */
SoundPlayer::SoundPlayer()
	: m_audioEngine(std::make_unique<AudioEngine>())
{
}

/**
 * \brief デストラクタ
 * 
 */
SoundPlayer::~SoundPlayer()
{
}

/**
 * \brief 更新
 * 
 */
void SoundPlayer::Update()
{
	if (!m_audioEngine->Update())
	{
		if (m_audioEngine->IsCriticalError())
		{
			m_audioEngine->Reset();
		}
	}
}

/**
 * \brief BGMの再生
 * 
 * \param soundManager サウンド管理
 */
void SoundPlayer::PlayBgm(ISoundManager* soundManager)
{
	SoundEffect* bgmSound = soundManager->GetBgmSound(m_playBgmCommand);

	if (bgmSound == nullptr) return;

	m_currentBgm = bgmSound->CreateInstance();

	// 音量の設定
	m_currentBgm->SetVolume(m_bgmValume);
	// ループ再生
	m_currentBgm->Play(true);
}

/**
 * \brief SEの再生
 * 
 * \param soundManager サウンド管理
 */
void SoundPlayer::PlaySe(ISoundManager* soundManager)
{
	for (auto& playCommand : m_playSeCommand)
	{
		SoundEffect* seSound = soundManager->GetSeSound(playCommand);

		if (seSound != nullptr)
		{
			seSound->Play(m_seValume, 1.0f, 0.0f);
		}
	}
}

/**
 * \brief BGM再生命令の登録
 * 
 * \param key キー
 */
void SoundPlayer::RegisterPlayBgmCommand(const std::string& key)
{
	m_playBgmCommand = key;
}

/**
 *  \brief 現在BGMの再開命令の登録 
 * 
 */
void SoundPlayer::RegisterResumeCurrentBgm()
{
	if (m_currentBgm.get() != nullptr)
	{
		m_currentBgm->Resume();
	}
}

/**
 * \brief 現在BGMの一時停止命令の登録
 * 
 */
void SoundPlayer::RegisterPauseCurrentBgm()
{
	if (m_currentBgm.get() != nullptr)
	{
		m_currentBgm->Pause();
	}
}

/**
 *\brief SE再生命令の登録
 * 
 * \param key キー
 */
void SoundPlayer::RegisterPlaySeCommand(const std::string& key)
{
	m_playSeCommand.push_back(key);
}
