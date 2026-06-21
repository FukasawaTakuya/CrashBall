/*****************************************************************//**
 * \file   FadeChangeScreen.h
 * \brief  フェードシーン遷移演出
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once

#include "Game/GameObject/GameObject.h"
#include "Game/Component/Default/Physics/RectTransform.h"
#include "Game/Component/Default/Renderer/SpriteRenderer.h"

/**
 * @brief フェードシーン遷移演出
 */
class  FadeChangeScreen : public GameObject {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	// コンポーネントのキャッシュ
	RectTransform* m_rectTransform = nullptr;
	SpriteRenderer* m_spriteRenderer = nullptr;

	bool m_isFadeOut = false;	// フェードインフラグ
	bool m_isFadeIn  = false;	// フェードアウトフラグ

	bool m_isEndFadeIn  = false;	// フェードイン終了フラグ
	bool m_isEndFadeOut = false;	// フェードアウト終了フラグ

	float m_alpha = 1.0f;	// 透明度

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	FadeChangeScreen();

	// デストラクタ
	~FadeChangeScreen();

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

	// フェードインの開始
	void StartFadeIn()
	{
		m_isFadeIn = true;
		m_isFadeOut = false;
		m_isEndFadeIn = false;
		m_alpha = 1.0f;
	}

	// フェードアウトの開始
	void StartFadeOut()
	{
		m_isFadeOut = true;
		m_isFadeIn = false;
		m_isEndFadeOut = false;
		m_alpha = 0.0f;
	}

	// 取得/設定
public:

	// フェードイン終了フラグの取得
	bool GetIsEndFadeInEnd() const
	{
		return m_isEndFadeIn;
	}

	// フェードアウト終了フラグの取得
	bool GetIsEndFadeOut() const
	{
		return m_isEndFadeOut;
	}

	// 内部実装
private:

};
