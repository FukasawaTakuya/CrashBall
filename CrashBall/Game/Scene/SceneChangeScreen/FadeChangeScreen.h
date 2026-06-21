#pragma once

#include "Game/GameObject/GameObject.h"
#include "Game/Component/Default/Physics/RectTransform.h"
#include "Game/Component/Default/Renderer/SpriteRenderer.h"

/**
 * @brief 基底オブジェクト
 */
class  FadeChangeScreen : public GameObject {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	RectTransform* m_rectTransform = nullptr;
	SpriteRenderer* m_spriteRenderer = nullptr;

	bool m_isFadeOut = false;
	bool m_isFadeIn = false;

	bool m_isEndFadeIn = false;
	bool m_isEndFadeOut = false;

	float m_alpha = 1.0f;

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

	void StartFadeIn()
	{
		m_isFadeIn = true;
		m_isFadeOut = false;
		m_isEndFadeIn = false;
		m_alpha = 1.0f;
	}

	void StartFadeOut()
	{
		m_isFadeOut = true;
		m_isFadeIn = false;
		m_isEndFadeOut = false;
		m_alpha = 0.0f;
	}

	// 取得/設定
public:

	bool GetIsEndFadeInEnd() const
	{
		return m_isEndFadeIn;
	}

	bool GetIsEndFadeOut() const
	{
		return m_isEndFadeOut;
	}

	// 内部実装
private:

};
