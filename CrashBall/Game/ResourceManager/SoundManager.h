/*****************************************************************//**
 * \file   SoundManager.h
 * \brief  サウンド管理クラス
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once
#include "Game/SoundPlayer/ISoundManager.h"

/**
 * @brief サウンド管理クラス
 */
class  SoundManager : public ISoundManager {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	using FileCollection
		= std::unordered_map<std::string, std::wstring>;
	using SoundCollection
		= std::unordered_map<std::string, std::unique_ptr<DirectX::SoundEffect>>;

	FileCollection	m_bgmfile;	// BGMのファイル名 
	FileCollection	m_sefile;	// SEのファイル名
	SoundCollection	m_bgmSounds;	// BGMのキャッシュ
	SoundCollection	m_seSounds;		// SEのキャッシュ

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	SoundManager();

	// デストラクタ
	~SoundManager();

	// 操作
public:

	// BGMのファイル名を登録
	void RegisterBgmFile(const std::string& key, const std::wstring& fileName);

	// SEのファイル名を登録
	void RegisterSeFile(const std::string& key, const std::wstring& fileName);

	// 音声の作成
	void CreateSound(DirectX::AudioEngine* audioEngine);


	// 取得/設定
public:

	// BGMの取得
	DirectX::SoundEffect* GetBgmSound(const std::string key) override;

	// SEの取得
	DirectX::SoundEffect* GetSeSound(const std::string key) override;

	// 内部実装
private:

};
