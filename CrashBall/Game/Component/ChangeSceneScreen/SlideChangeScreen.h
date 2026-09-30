/*****************************************************************//**
 * \file   SlideChangeScreen.h
 * \brief  スライド遷移スクリーン
 * 
 * \author 深沢拓矢
 * \date   September 2026
 *********************************************************************/

#pragma once

#include "ChangeSceneScreen.h"

/**
 * @brief
 */
class  SlideChangeScreen : public ChangeSceneScreen {

	// メンバ変数の宣言 -------------------------------------------------

	Easing<float> m_fillAmount;

	// コンポーネント名の設定
	SetCompName("SlideChangeScreen")

		// メンバ関数の宣言 -------------------------------------------------
		// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	SlideChangeScreen(IGameObject* gameObject);

	// デストラクタ
	~SlideChangeScreen() = default;

	// 操作
public:

	// アタッチ時の処理
	void Awake() override;
	// 開始処理
	void Start(const GameContext& gameContext) override;
	// 更新
	void Update(const GameContext& gameContext) override;

	// シーンに入る
	void SceneIn() override;

	// シーンから出る
	void SceneOut() override;

	// 内部実装
private:

	// コンポーネント名の取得
	virtual std::string GetCompName() const override
	{
		return m_compName;
	}
};