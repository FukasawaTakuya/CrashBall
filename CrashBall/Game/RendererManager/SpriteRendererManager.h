/*****************************************************************//**
 * \file   SpriteRendererManager.h
 * \brief  スプライト描画管理クラス
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once

#include "Game/RendererManager/Interface/ISpriteRendererManager.h"

/**
 * @brief スプライト描画管理クラス
 */
class  SpriteRendererManager : public ISpriteRendererManager {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;	// スプライトバッチ

	std::vector<SpriteRenderCommand> m_renderCommad;		// 描画命令コンテナ

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	SpriteRendererManager();

	// デストラクタ
	~SpriteRendererManager();

	// 操作
public:

	// 描画
	void Render(DirectX::SpriteBatch* spriteBatch);

	// 描画命令の登録
	void RegisterRenderCommand(
		ID3D11ShaderResourceView* pSprite,
		const DirectX::SimpleMath::Vector2& position,
		const RECT& srcRect,
		const DirectX::XMVECTORF32& color,
		float rotate,
		float scale,
		const DirectX::SimpleMath::Vector2& origin,
		DirectX::SpriteEffects spriteEffects,
		float layerDepth) override;

	// 描画命令の登録
	void RegisterRenderCommand(
		ID3D11ShaderResourceView* pSprite,
		const DirectX::SimpleMath::Vector2& position,
		const RECT& srcRect,
		const DirectX::XMVECTORF32& color,
		float rotate,
		const DirectX::SimpleMath::Vector2& scale,
		const DirectX::SimpleMath::Vector2& origin,
		DirectX::SpriteEffects spriteEffects,
		float layerDepth) override;

	// 描画命令のクリア
	void ClearRenderCommand();

	// スプライトバッチの作成
	void Create(ID3D11DeviceContext1* context);

	// 取得/設定
public:

	// 内部実装
private:

};
