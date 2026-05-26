/*****************************************************************//**
 * \file   SpriteManager.h
 * \brief  スプライト管理クラス
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#include "Game/Interface/ISpriteManager.h"

#pragma once

/**
 * @brief スプライト管理クラス
 */
class  SpriteManager : public ISpriteManager {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	// エイリアス宣言
	using FileCollection
		= std::unordered_map<std::string, const wchar_t*>;
	using SpriteCollection
		= std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>>;

	FileCollection		m_factory;	// スプライトファクトリー
	SpriteCollection	m_sprites;	// スプライトのキャッシュ


	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	SpriteManager();

	// デストラクタ
	~SpriteManager();

	// 操作
public:

	// ファクトリーに登録
	void RegisterFactory(std::string key, const wchar_t* fileName);

	// モデルの作成
	void CreateSprite(ID3D11Device1* device);

	// 取得/設定
public:

	// モデルの取得
	ID3D11ShaderResourceView* GetSprite(const std::string& key) override ;

	// 内部実装
private:

};
