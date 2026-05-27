/*****************************************************************//**
 * \file   SoundManager.h
 * \brief  サウンド管理クラス
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once
#include "Game/Interface/ISoundManager.h"

/**
 * @brief サウンド管理クラス
 */
class  SoundManager : public ISoundManager {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	using FileCollection
		= std::unordered_map<std::string, const wchar_t*>;
	using SoundCollection
		= std::unordered_map<std::string, std::unique_ptr<DirectX::SoundEffect>>;

	FileCollection	m_bgmfactory;	// 
	FileCollection	m_sefactory;
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

	void RegisterFactory(const std::string& key, const wchar_t* fileName);

	// 音声の作成
	void CreateSound(DirectX::AudioEngine* audioEngine);


	// 取得/設定
public:

	// BGMの取得
	DirectX::SoundEffect* GetBgmSound(const std::string key);

	// SEの取得
	DirectX::SoundEffect* GetSeSound(const std::string key);



	// 内部実装
private:

};
