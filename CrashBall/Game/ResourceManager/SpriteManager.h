/*****************************************************************//**
 * \file   SpriteManager.h
 * \brief  スプライト管理クラス
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/
#pragma once
#include "Game/ResourceManager/Interface/ISpriteManager.h"

/**
 * @brief スプライト管理クラス
 */
class  SpriteManager : public ISpriteManager {

	// メンバ変数の宣言 -----------------------------------------------
private:

	using SpriteInfoCollection 
		= std::unordered_map<std::string, SpriteInfo>;

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

	// スプライトの作成
	void CreateSprite(ID3D11Device1* device);


	// 取得/設定
public:

	// スプライト情報の取得
	const SpriteInfo* GetSpriteInfo(const std::string& key) const override;

	// 内部実装
private:

};
