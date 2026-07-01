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
	Slider(json* data);

	// デストラクタ
	~Slider();

	// 操作
public:

	// 初期化
	void Initialize();

	// 更新
	void Update(const GameContext& gameContext);

	// 描画
	void Render(const RenderContext& renderContext);

	// 終了処理
	void Finalize();

	// パラメータの書き込み
	void SaveParam() override;

	// 初期化用のパラメータの書き込み
	void SaveInitParam() override;

	// データの再読み込み
	void ReloadParam() override;

	// 取得/設定
public:

	// 内部実装
private:

};
