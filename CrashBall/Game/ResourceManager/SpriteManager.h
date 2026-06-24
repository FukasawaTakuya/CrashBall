/*****************************************************************//**
 * \file   SpriteManager.h
 * \brief  スプライト管理クラス
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#include "Game/ResourceManager/Interface/ISpriteManager.h"

#pragma once

/**
 * @brief スプライト管理クラス
 */
class  SpriteManager : public ISpriteManager {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	using FileCollection
		= std::unordered_map<std::string, std::wstring>;
	using SpriteCollection
		= std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>>;
	using SpriteSizeCollection = std::unordered_map<std::string, DirectX::SimpleMath::Vector2>;

	FileCollection		m_files;	// ファイル名
	SpriteCollection	m_sprites;	// スプライトのキャッシュ
	
	SpriteSizeCollection m_spriteSizes;	// スプライトのサイズ


	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	SpriteManager();

	// デストラクタ
	~SpriteManager();

	// 操作
public:

	// ファイル名を登録
	void RegisterFile(const std::string& key, const std::wstring& fileName);

	// モデルの作成
	void CreateSprite(ID3D11Device1* device);

	// スプライト描画コンポーネントのセットアップ
	void SetUpSpriteRenderer(SpriteRenderer* spriteRenderer) override;

	// 取得/設定
public:

	// モデルの取得
	ID3D11ShaderResourceView* GetSprite(const std::string& key) override;

	// 内部実装
private:

};
