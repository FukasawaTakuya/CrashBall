/*****************************************************************//**
 * \file   TitleLogo.h
 * \brief  タイトルロゴ
 * 
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#pragma once

#include "Game/GameObject/UIObject/Object2D.h"
#include "Game/Component/Default/UI/SpriteBobbing.h"

/**
 * @brief 
 */
class  TitleLogo : public Object2D {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	// コンポーネントのキャッシュ
	SpriteBobbing* m_spriteBobbing = nullptr;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	TitleLogo();

	// コンストラクタ
	TitleLogo(ordered_json* data);

	// デストラクタ
	~TitleLogo();

	// 操作
public:

	// 初期化
	void Start(const GameContext& gameContext) override;

	// 更新
	void Update(const GameContext& gameContext) override;

	// 描画
	void Render(const RenderContext& renderContext) override;

	// 終了処理
	void Finalize();

	// 取得/設定
public:

	// 内部実装
private:

};
