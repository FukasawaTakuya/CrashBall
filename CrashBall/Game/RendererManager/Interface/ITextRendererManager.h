#pragma once

#include <string>
#include <SimpleMath.h>

struct TextRenderCommand
{
	DirectX::SpriteFont* pSpriteFont;		// スプライトフォント
	DirectX::SimpleMath::Vector2 position;	// 描画位置
	DirectX::SimpleMath::Color color;		// 色
	float rotate;							// 回転
	DirectX::SimpleMath::Vector2 scale;		// スケール
	DirectX::SimpleMath::Vector2 origin;	// 基準位置
	float layerDepth;						// 描画順
	std::wstring text;						// テキスト
};


/**
 * \brief テキスト描画管理クラスのインターフェース
 */
class  ITextRendererManager {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:



	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	ITextRendererManager() = default;

	// デストラクタ
	~ITextRendererManager() = default;

	// 操作
public:

	// 取得/設定
public:

	// 描画命令の登録
	virtual void RegisterRenderCommand(
		DirectX::SpriteFont* pSpriteFont,
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Color& color,
		float rotate,
		const DirectX::SimpleMath::Vector2& scale,
		const DirectX::SimpleMath::Vector2& origin,
		float layerDepth,
		const std::wstring& text) = 0;

	// デバッグ描画
	virtual void DebugRender(
		const DirectX::SimpleMath::Vector2& position,
		const std::wstring& text) = 0;

	// 書式付文字列のデバッグ描画描画命令の登録
	template<typename ...Args>
	inline void DebugRender(
		const DirectX::SimpleMath::Vector2& position,
		std::wformat_string<Args...> fmt,
		Args&& ...args)
	{
		DebugRender(
			position,
			std::format(fmt, std::forward<Args>(args)...)
		);
	}

	// 内部実装
private:

};
