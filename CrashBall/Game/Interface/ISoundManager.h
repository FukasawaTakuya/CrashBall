#pragma once
#include <Audio.h>

/**
 * @brief サウンド管理クラスのインターフェース
 */
class  ISoundManager {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:


	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	ISoundManager() = default;

	// デストラクタ
	~ISoundManager() = default;

	// 操作
public:

	// 取得/設定
public:

	// BGMの取得
	virtual DirectX::SoundEffect* GetBgmSound(const std::string key) = 0;

	// SEの取得
	virtual DirectX::SoundEffect* GetSeSound(const std::string key) = 0;

	// 内部実装
private:

};
