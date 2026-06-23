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
#include <SpriteBatch.h>

// 描画命令
struct SpriteRenderCommand
{
	ID3D11ShaderResourceView* pSprite;		// スプライト
	DirectX::SimpleMath::Vector2 position;	// 描画位置
	RECT srcRect;							// 切り取り領域
	DirectX::SimpleMath::Color color;		// 色
	float rotate;							// 回転
	DirectX::SimpleMath::Vector2 scale;		// スケール
	DirectX::SimpleMath::Vector2 origin;	// 基準位置
	DirectX::SpriteEffects spriteEffects;	// 反転
	float layerDepth;						// 描画順
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
		const DirectX::SimpleMath::Vector2& position,
		const RECT& srcRect,
		const DirectX::SimpleMath::Color& color,
		float rotate,
		float scale,
		const DirectX::SimpleMath::Vector2& origin,
		DirectX::SpriteEffects spriteEffects,
		float layerDepth) = 0;

	virtual void RegisterRenderCommand(
		ID3D11ShaderResourceView* pSprite,
		const DirectX::SimpleMath::Vector2& position,
		const RECT& srcRect,
		const DirectX::SimpleMath::Color& color,
		float rotate,
		const DirectX::SimpleMath::Vector2& scale,
		const DirectX::SimpleMath::Vector2& origin,
		DirectX::SpriteEffects spriteEffects,
		float layerDepth) = 0;


	// 取得/設定
public:

	// 内部実装
private:

};
