/*****************************************************************//**
 * \file   ISpriteManager.h
 * \brief  スプライト管理クラスのインターフェース
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once
#include <d3d11.h>
#include <string>

class SpriteRenderer;

/**
 * @brief スプライト管理クラスのインターフェース
 */
class  ISpriteManager {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	ISpriteManager() = default;

	// デストラクタ
	virtual ~ISpriteManager() = default;

	// 操作
public:

	// スプライト描画コンポーネントのセットアップ
	virtual void SetUpSpriteRenderer(SpriteRenderer* spriteRenderer) = 0;

	// 取得/設定
public:

	// スプライトの取得
	virtual ID3D11ShaderResourceView* GetSprite(const std::string& key) = 0;

	// 内部実装
private:

};
