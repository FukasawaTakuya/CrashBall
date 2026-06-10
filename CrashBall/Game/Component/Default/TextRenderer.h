/*****************************************************************//**
 * \file   TextRenderer.h
 * \brief  テキスト描画コンポーネント
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once

#include "Component.h"
#include "Game/Context/RenderContext.h"
#include "RectTransform.h"

/**
 * @brief テキスト描画コンポーネント
 */
class  TextRenderer : public Component {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	DirectX::SpriteFont* m_pSpriteFont = nullptr;			// スプライトフォント
	std::wstring m_text;									// テキスト
	DirectX::XMVECTORF32 m_color = DirectX::Colors::White;	// 色
	float m_fontScale = 1.0f;								// フォントのスケール
	float m_width = 0.0f;									// 横幅
	float m_height = 0.0f;									// 縦幅
	float m_layerDepth = 1.0f;								// 描画順
	RectTransform* m_rectTransform = nullptr;				// トランスフォームのキャッシュ
		
	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	TextRenderer(IGameObject* gameObject);

	// デストラクタ
	~TextRenderer();

	// 操作
public:

	void Render(ITextRendererManager* rendererManager);

	// 取得/設定
public:

	// スプライトフォントの設定
	void SetSpriteFont(DirectX::SpriteFont* pSpriteFont)
	{
		m_pSpriteFont = pSpriteFont;
	}

	// 描画順の設定
	void SetLayerDepth(float layerDepth)
	{
		m_layerDepth = layerDepth;
	}

	// 色の設定
	void SetColor(const DirectX::XMVECTORF32& color)
	{
		m_color = color;
	}

	// フォントのスケールの設定
	void SetFontScale(float fontScale)
	{
		m_fontScale = fontScale;
	}

	// テキストの設定
	void SetText(const std::wstring& text)
	{
		if (m_pSpriteFont == nullptr) return;

		m_text = text;

		// サイズを求める
		DirectX::SimpleMath::Vector2 textSize = m_pSpriteFont->MeasureString(m_text.c_str());
		m_width = textSize.x;
		m_height = textSize.y;
	}

	// 書式付のテキストの設定
	template<typename... Args>
	void SetText(
		std::wformat_string<Args...> format, 
		Args&&... args)
	{
		SetText(std::format(format, std::forward<Args>(args)...));
	}

	// 内部実装
private:

};
