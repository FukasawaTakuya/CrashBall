/*****************************************************************//**
 * \file   Object2D.h
 * \brief  2Dオブジェクト
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once

#include "Game/GameObject/GameObject.h"
#include "Game/Component/Default/Physics/RectTransform.h"
#include "Game/Component/Default/Renderer/SpriteRenderer.h"

/**
 * @brief 2Dオブジェクト
 */
class  Object2D : public GameObject {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	// スプライト描画コンポーネントのキャッシュ
	SpriteRenderer* m_spriteRenderer = nullptr;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Object2D();


	Object2D(json* data);

	// デストラクタ
	~Object2D();

	// 操作
public:

	// 初期化
	virtual void Initialize() override;

	// 更新
	virtual void Update(const GameContext& gameContext) override;

	// 描画
	virtual void Render(const RenderContext& renderContext) override;

	// 終了処理
	virtual void Finalize() override;

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
