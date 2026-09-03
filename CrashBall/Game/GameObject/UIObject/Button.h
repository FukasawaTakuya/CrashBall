/*****************************************************************//**
 * \file   Button.h
 * \brief  ボタン
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once

#include "Game/GameObject/GameObject.h"

#include "Game/Component/Default/UI/ButtonController.h"

/**
 * @brief ボタン
 */
class  Button : public GameObject {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
protected:

	// コンポーネントのキャッシュ
	RectTransform*		m_rectTransform		 = nullptr;
	SpriteRenderer*		m_spriteRenderer	 = nullptr;
	TextRenderer*		m_textRenderer		 = nullptr;
	ButtonController*	m_buttonController	 = nullptr;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Button();

	// 
	Button(ordered_json* data);

	// デストラクタ
	~Button();

	// 操作
public:

	// 初期化
	void Start(const GameContext& gameContext);

	// 更新
	void Update(const GameContext& gameContext);

	// 描画
	void Render(const RenderContext& renderContext);

	// 終了処理
	void Finalize();

	// パラメータの書き込み
	void SaveParam() override;

	// データの再読み込み
	void ReloadParam() override;

	// 取得/設定
public:

	// 内部実装
private:

};
