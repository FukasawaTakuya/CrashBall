#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include <DirectXColors.h>
#include <SpriteFont.h>

struct SpriteRenderCmd
{
	ID3D11ShaderResourceView* pSprite;
	RECT rect;
	DirectX::XMVECTORF32 color;
};


/**
 * @brief 基底オブジェクト
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
		const DirectX::XMVECTORF32 color = DirectX::Colors::White) = 0;

	//virtual void RednerText() = 0;


	// 取得/設定
public:

	// 内部実装
private:

};
