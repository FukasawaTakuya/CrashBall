/*****************************************************************//**
 * \file   TextManager.h
 * \brief  テキスト管理クラス
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once
#include "Game/ResourceManager/Interface/ITextManager.h"

/**
 * @brief テキスト管理クラス
 */
class  TextManager : public ITextManager {

	// メンバ変数の宣言 -----------------------------------------------
private:

	using SpriteFontCollection = std::unordered_map<std::string, std::unique_ptr<DirectX::SpriteFont>>;

	SpriteFontCollection m_spriteFonts;	// スプライトフォント

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	TextManager();

	// デストラクタ
	~TextManager();

	// 操作
public:

	// スプライトフォントの作成
	void CreateSpriteFont(ID3D11Device1* device);

	// 取得/設定
public:

	// スプライトフォントの取得
	DirectX::SpriteFont* GetSpriteFont(const std::string& key) const ;

	// 内部実装
private:

};
