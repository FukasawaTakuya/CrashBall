/*****************************************************************//**
 * \file   TextRendererManager.h
 * \brief  テキスト描画管理クラス
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once

#include "Game/RendererManager/Interface/ITextRendererManager.h"

/**
 * @brief テキスト描画管理クラス
 */
class  TextRendererManager : public ITextRendererManager{

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	std::unique_ptr<DirectX::SpriteFont> m_debugFont;	// デバッグ用のフォント

	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;	// スプライトバッチ

	std::vector<TextRenderCommand> m_renderCommad;	// 描画命令コンテナ

	std::vector<TextRenderCommand> m_debugRenderCommad;	// デバッグ描画命令コンテナ

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	TextRendererManager();

	// デストラクタ
	~TextRendererManager();

	// 操作
public:

	void Render(DirectX::SpriteBatch* spriteBatch);

	// 描画命令の登録
	void RegisterRenderCommand(
		DirectX::SpriteFont* pSpriteFont,
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::XMVECTORF32& color,
		float rotate,
		float scale,
		const DirectX::SimpleMath::Vector2& origin,
		float layerDepth,
		const std::wstring& text) override;

	// デバッグ描画
	void DebugRender(
		const DirectX::SimpleMath::Vector2& position,
		const std::wstring& text) override;

	using ITextRendererManager::DebugRender;

	void ClearnRenderCommand();

	void Create(
		ID3D11Device1* device,
		ID3D11DeviceContext1* context);

	// 取得/設定
public:

	// 内部実装
private:

};