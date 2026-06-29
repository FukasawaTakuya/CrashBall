/*****************************************************************//**
 * \file   Panel.h
 * \brief  UIをまとめるパネルオブジェクト
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once

#include "Game/GameObject/GameObject.h"

#include "Game/Component/Default/Physics/RectTransform.h"

/**
 * @brief UIをまとめるパネルオブジェクト
 */
class  Panel : public GameObject {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:


	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Panel();

	// デストラクタ
	Panel(json* data);

	// デストラクタ
	virtual ~Panel();

	// 操作
public:

	// 初期化
	virtual void Initialize() = 0;

	// 更新
	virtual void Update(const GameContext& gameContext) = 0;

	// 描画
	virtual void Render(const RenderContext& RenderContext) = 0;

	// 終了処理
	virtual void Finalize() = 0;

	// 取得/設定
public:

	// 内部実装
private:

};
