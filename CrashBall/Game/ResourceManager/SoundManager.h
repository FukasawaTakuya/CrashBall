/*****************************************************************//**
 * \file   SoundManager.h
 * \brief  サウンド管理クラス
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once

/**
 * @brief サウンド管理クラス
 */
class  SoundManager {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	// エイリアス宣言
	using FileCollection
		= std::unordered_map<std::string, const wchar_t*>;
	using SoundCollection
		= std::unordered_map<std::string, std::unique_ptr<DirectX::SoundEffect>>;

	FileCollection	m_bgmfactory;	// 
	FileCollection	m_sefactory;
	SoundCollection	m_bgmSounds;	// BGMのキャッシュ
	SoundCollection	m_seSounds;		// SEのキャッシュ

	// TODO:AudioEngine持たせるか

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	SoundManager() = default;

	// デストラクタ
	~SoundManager();

	// 操作
public:

	void CreateSound();

	void PlayBGM(const std::string& key);

	void StopBGM();

	void PlaySE(const std::string& key);

	// 取得/設定
public:

	// 内部実装
private:

};
