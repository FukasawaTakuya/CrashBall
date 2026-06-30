/*****************************************************************//**
 * \file   TextRenderer.h
 * \brief  テキスト描画コンポーネント
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once

#include "..\Component.h"
#include "Game/Context/RenderContext.h"
#include "..\Physics\RectTransform.h"

/**
 * @brief テキスト描画コンポーネント
 */
class  TextRenderer : public Component {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	DirectX::SpriteFont* m_pSpriteFont = nullptr;					// スプライトフォント
	std::wstring m_text;											// テキスト
	DirectX::SimpleMath::Color m_color = {1.0f, 1.0f, 1.0f, 1.0f };	// 色
	float m_fontScale = 1.0f;										// フォントのスケール
	float m_width = 0.0f;											// 横幅
	float m_height = 0.0f;											// 縦幅
	float m_layerDepth = 0.0f;										// 描画順

	RectTransform* m_rectTransform = nullptr;	// トランスフォームのキャッシュ
		
	std::string m_fontKey;	// スプライトフォントのキー

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// デフォルトコンストラクタ
	TextRenderer() = default;

	// コンストラクタ
	TextRenderer(IGameObject* gameObject);

	// コピーコンストラクタ
	TextRenderer(
		IGameObject* gameObject,
		const TextRenderer& other);

	// デストラクタ
	~TextRenderer();

	// 操作
public:

	void Render(ITextRendererManager* rendererManager);

	// 取得/設定
public:

	// スプライトフォントのキーの取得 
	std::string GetFontKey() const
	{
		return m_fontKey;
	}

	// スプライトフォントの設定
	void SetSpriteFont(DirectX::SpriteFont* pSpriteFont)
	{
		m_pSpriteFont = pSpriteFont;

		// 
		CalcTextSize();
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
		m_text = text;

		if (m_pSpriteFont == nullptr) return;

		CalcTextSize();
	}

	// 書式付のテキストの設定
	template<typename... Args>
	void SetText(
		std::wformat_string<Args...> format, 
		Args&&... args)
	{
		SetText(std::format(format, std::forward<Args>(args)...));
	}

	// スプライトフォントのキーの設定
	void SetFontKey(const std::string& fontKey)
	{
		m_fontKey = fontKey;
	}

	// 内部実装
private:

	// テキストのサイズを求める
	void CalcTextSize()
	{
		DirectX::SimpleMath::Vector2 textSize = m_pSpriteFont->MeasureString(m_text.c_str());
		m_width = textSize.x;
		m_height = textSize.y;
	}

	// JsonConvert
private:
	friend void from_json(const json& j, TextRenderer& textRenderer);
	friend void to_json(json& j, const TextRenderer& textRenderer);

	// 演算子オーバーロード
public:

	void operator=(const TextRenderer& other)
	{
		m_text	= other.m_text;
		m_color = other.m_color;
		m_fontScale = other.m_fontScale;
		m_layerDepth = other.m_layerDepth;
	}
};
