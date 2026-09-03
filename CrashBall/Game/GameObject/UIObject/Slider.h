/*****************************************************************//**
 * \file   Slider.h
 * \brief  スライダー
 * 
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#pragma once

#include "Game/GameObject/GameObject.h"

#include "Game/Component/Default/Physics/RectTransform.h"
#include "Game/Component/Default/Renderer/SpriteRenderer.h"
#include "Game/Component/Default/UI/SliderController.h"

/**
 * @brief スライダー
 */
class  Slider : public GameObject {

	// データメンバの宣言 -----------------------------------------------
private:

	// コンポーネントのキャッシュ
	SpriteRenderer* m_spriteRenderer = nullptr;
	SliderController* m_sliderController = nullptr;


	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Slider();

	// コンストラクタ
	Slider(ordered_json* data);

	// デストラクタ
	~Slider();

	// 操作
public:

	// 初期化
	void Start(const GameContext& gameContext) override;

	// 更新
	void Update(const GameContext& gameContext) override;

	// 描画
	void Render(const RenderContext& renderContext) override;

	// パラメータの書き込み
	void SaveParam() override;

	// データの再読み込み
	void ReloadParam() override;

	// 取得/設定
public:

	// 内部実装
private:

};
