/*****************************************************************//**
 * \file   FadeChageScreen.h
 * \brief  フェード遷移スクリーン
 * 
 * \author 深沢拓矢
 * \date   September 2026
 *********************************************************************/

#pragma once

#include "ChangeSceneScreen.h"

/**
 * @brief フェード遷移スクリーン
 */
class  FadeChageScreen : public ChangeSceneScreen {

	// メンバ変数の宣言 -------------------------------------------------

	Easing<float> m_alpha;


	// コンポーネント名の設定
	SetCompName("FadeChageScreen")

		// メンバ関数の宣言 -------------------------------------------------
		// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	FadeChageScreen(IGameObject* gameObject);

	// デストラクタ
	~FadeChageScreen() = default;

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