/*****************************************************************//**
 * \file   Object3D.h
 * \brief  3Dオブジェクト
 *
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#pragma once

#include "GameObject.h"

#include "Game/Component/Default/Renderer/ModelRenderer.h"
#include "Game/Component/Default/Physics/Transform.h"

/**
 * @brief 3Dオブジェクト
 */
class  Object3D : public GameObject {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	// モデルレンダラーのキャッシュ
	ModelRenderer* m_modelRenderer = nullptr;
	Transform* m_transform = nullptr;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Object3D();

	// デストラクタ
	~Object3D();

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


	// 取得/設定
public:

	// 内部実装
private:

};
