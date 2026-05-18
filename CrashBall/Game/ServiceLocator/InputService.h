/*****************************************************************//**
 * \file   InputService.h
 * \brief  入力取得クラスに関するヘッダーファイル
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once
#include "Game/Interface/IInputSystem.h"

/**
 * @brief 入力取得クラス
 */
class  InputService {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	IInputSystem* m_input;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
private:

	// コンストラクタ
	InputService() = default;

	// 複数生成の禁止
	InputService(InputService&) = delete;
	InputService& operator= (const InputService&) = delete;

	// デストラクタ
	~InputService() = default;

	// 操作
public:
	// インスタンスの取得
	static InputService& Instance() {
		static InputService instance;
		return instance;
	}

	// 取得/設定
public:

	// 入力の取得
	IInputSystem* GetInput() { return m_input; }

	// 入力システムのインターフェースの設定
	void SetInput(IInputSystem* input) { m_input = input; }

	// 内部実装
private:

};
