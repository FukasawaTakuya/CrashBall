#pragma once

#include <string>
#include <SimpleMath.h>

struct TextRenderCmd
{
	DirectX::SimpleMath::Vector2 position;
	DirectX::XMVECTORF32 color;
	float scale;
	DirectX::SimpleMath::Vector2 origin;
	float layerDepth;
	std::wstring text;
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
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::XMVECTORF32& color,
		float scale,
		const DirectX::SimpleMath::Vector2& origin,
		float layerDepth,
		const std::wstring& text) = 0;

	// 書式付文字列の描画命令の登録
	template<typename ...Arg>
	inline void RegisterRenderCommand(
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::XMVECTORF32& color,
		float scale,
		const DirectX::SimpleMath::Vector2& origin,
		float layerDepth,
		std::wformat_string<Arg...> fmt,
		Arg&& ...arg)
	{
		RegisterRenderCommand(
			position,
			color,
			scale,
			origin,
			layerDepth,
			std::format(fmt, std::forward<Arg>(arg)...)
		);
	}

	// 内部実装
private:

};
