/*****************************************************************//**
 * \file   SoundPlayer.h
 * \brief  サウンド再生クラス
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once

#include "Game/SoundPlayer/ISoundPlayer.h"
#include "Game/SoundPlayer/ISoundManager.h"

/**
 * @brief サウンド再生クラス
 */
class  SoundPlayer : public ISoundPlayer {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	std::unique_ptr<DirectX::AudioEngine> m_audioEngine;	// オーディオエンジン

	std::string m_playBgmCommand;	
	std::vector<std::string> m_playSeCommand;

	std::unique_ptr<DirectX::SoundEffectInstance> m_currentBgm;	// 現在流れているBGM

	float m_bgmValume = 1.0f;	// BGMのボリューム
	float m_seValume = 1.0f;	// SEのボリューム

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	SoundPlayer();

	// デストラクタ
	~SoundPlayer();

	// 操作
public:

	// 更新
	void Update();

	// BGMの再生
	void PlayBgm(ISoundManager* soundManager);
	// SEの再生
	void PlaySe(ISoundManager* soundManager);

	// BGMの再生命令の登録
	void RegisterPlayBgmCommand(const std::string& key) override;

	// 現在BGMの再開命令の登録 
	void RegisterResumeCurrentBgm() override;
	// 現在BGMの一時停止命令の登録
	void RegisterPauseCurrentBgm() override;

	// SEの再生命令の登録
	void RegisterPlaySeCommand(const std::string& key) override;


	// 取得/設定 
public: 

	// オーディオエンジンの取得
	DirectX::AudioEngine* GetAudioEngine()
	{
		return m_audioEngine.get();
	}

	// 内部実装 
private:

};
