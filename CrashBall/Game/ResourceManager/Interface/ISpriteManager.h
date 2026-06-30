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

struct SpriteInfo
{
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> sprite;
	float width = 0.0f;
	float height = 0.0f;
};


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

	// 取得/設定
public:

	// スプライト情報の取得
	virtual const SpriteInfo* GetSpriteInfo(const std::string& key) const = 0;

	// 内部実装
private:

};
