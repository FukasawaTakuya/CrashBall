#pragma once

#include "GameObject.h"
#include "Game/Component/Collider/Mesh.h"
#include "Game/Component/ModelRenderer.h"
#include "Game/Component/Transform.h"
#include "Game/Component/StageController.h"


/**
 * \brief ステージオブジェクト
 */
class  Stage : public GameObject {

	// クラス定数の宣言 -------------------------------------------------
private:

	// データメンバの宣言 -----------------------------------------------
private:

	StageController* m_stageController;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Stage();

	// デストラクタ
	~Stage();

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

	// 取得/設定
public:

	// 内部実装
private:

};
