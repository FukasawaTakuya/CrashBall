/*****************************************************************//**
 * \file   ISpriteRendererManager.h
 * \brief  スプライト描画管理クラスのインターフェース
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include <DirectXColors.h>
#include <SpriteFont.h>

// 描画命令
struct SpriteRenderCommand
{
	ID3D11ShaderResourceView* pSprite;
	RECT rect;
	int orderInLayer;
	DirectX::XMVECTORF32 color;
};


/**
 * @brief スプライト描画管理クラスのインターフェース
 */
class  ISpriteRendererManager {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:



	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	ISpriteRendererManager() = default;

	// デストラクタ
	virtual ~ISpriteRendererManager() = default;

	// 操作
public:

	// 描画命令の登録
	virtual void RegisterRenderCommand(
		ID3D11ShaderResourceView* pSprite,
		const RECT rect,
		int orderInLayer = 0,
		const DirectX::XMVECTORF32 color = DirectX::Colors::White) = 0;


	// 取得/設定
public:

	// 内部実装
private:

};
