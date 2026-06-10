/*****************************************************************//**
 * \file   ITextManager.h
 * \brief  テキスト管理クラスのインターフェース
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once
#include <SpriteFont.h>
#include <string>


/**
 * @brief テキスト管理クラスのインターフェース
 */
class  ITextManager {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:



	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	ITextManager() = default;

	// デストラクタ
	virtual ~ITextManager() = default;

	// 操作
public:

	// 取得/設定
public:

	virtual DirectX::SpriteFont* GetSpriteFont(const std::string& key) = 0;

	// 内部実装
private:

};
