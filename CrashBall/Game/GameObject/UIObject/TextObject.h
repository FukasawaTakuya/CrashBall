/*****************************************************************//**
 * \file   TextObject.h
 * \brief  テキスト描画オブジェクト
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once

#include "Game/GameObject/GameObject.h"
#include "Game/Component/Default/Renderer/TextRenderer.h"

/**
 * @brief テキスト描画オブジェクト
 */
class  TextObject : public GameObject{

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	// テキスト描画コンポーネントのキャッシュ
	TextRenderer* m_textRenderer = nullptr;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	TextObject();


	TextObject(json* data);

	// デストラクタ
	~TextObject();

	// 操作
public:

	// 初期化
	void Initialize() override;

	// 更新
	void Update(const GameContext& gameContext) override;

	// 描画
	void Render(const RenderContext& renderContext) override;

	// 終了処理
	void Finalize() override;

	// パラメータの書き込み
	void SaveParam() override;

	// 初期化用のパラメータの書き込み
	void SaveInitParam() override;

	// データの再読み込み
	void ReloadParam() override;


	// 取得/設定
public:

	// テキストの設定
	void SetText(const std::wstring& text)
	{
		m_textRenderer->SetText(text);
	}

	template<typename... Args>
	void SetText(std::wformat_string<Args...> fmt, 
		Args&&... args)
	{
		SetText(std::format(fmt, std::forward<Args>(args)...));
	}

	// 内部実装
private:

};
