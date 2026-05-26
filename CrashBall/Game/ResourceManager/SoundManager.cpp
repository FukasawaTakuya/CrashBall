#include "pch.h"
#include "SoundManager.h"

using namespace DirectX;

SoundManager::~SoundManager()
{
}

void SoundManager::CreateSound()
{
	for (auto& file : m_bgmfactory)
	{
		m_bgmSounds.emplace(std::make_unique<SoundEffect>())
	}
}

void SoundManager::PlayBGM(const std::string& key)
{
}

void SoundManager::StopBGM()
{
}

void SoundManager::PlaySE(const std::string& key)
{
}
