#pragma once

#include "Game/Interface/ITextRendererManager.h"



/**
 * @brief テキスト描画管理クラス
 */
class  TextRendererManager : public ITextRendererManager{

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	std::unique_ptr<DirectX::SpriteFont> m_spriteFont;	// スプライトフォント

	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;	// スプライトバッチ

	std::vector<TextRenderCommand> m_renderCommad;	// 描画命令コンテナ

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
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::XMVECTORF32& color,
		float scale,
		const DirectX::SimpleMath::Vector2& origin,
		float layerDepth,
		const std::wstring& text) override;

	using ITextRendererManager::RegisterRenderCommand;

	void ClearnRenderCommand();

	void Create(
		ID3D11Device1* device,
		ID3D11DeviceContext1* context);

	// 取得/設定
public:

	// 内部実装
private:

};