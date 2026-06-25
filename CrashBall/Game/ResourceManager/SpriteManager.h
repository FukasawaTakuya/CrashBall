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
	using SpriteInfoCollection 
		= std::unordered_map<std::string, SpriteInfo>;

	FileCollection		m_files;		// ファイル名
	SpriteInfoCollection m_spriteInfo;	// スプライト情報
	

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

	// スプライトの作成
	void CreateSprite(ID3D11Device1* device);


	// 取得/設定
public:

	// スプライト情報の取得
	SpriteInfo* GetSpriteInfo(const std::string& key) override;

	// 内部実装
private:

};
