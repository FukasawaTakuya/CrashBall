/*****************************************************************//**
 * \file   ISoundPlayer.h
 * \brief  音声再生クラスのインターフェース
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/


#pragma once
#include <string>

/**
 * \brief 音声再生クラスのインターフェース
 */
class  ISoundPlayer {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:



	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	ISoundPlayer() = default;

	// デストラクタ
	~ISoundPlayer() = default;

	// 操作
public:

	// BGMの再生
	virtual void RegisterPlayBgmCommand(const std::string& key) = 0;

	// 現在のBGMを再生
	virtual void RegisterResumeCurrentBgm() = 0;
	// 現在のBGMを停止
	virtual void RegisterPauseCurrentBgm() = 0;

	// SEの再生
	virtual void RegisterPlaySeCommand(const std::string& key) = 0;

	// 取得/設定
public:

	// 内部実装
private:

};
