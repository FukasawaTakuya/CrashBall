#pragma once

#include "Game/GameObject/GameObject.h"
#include "Game/Component/Default/RectTransform.h"
#include "Game/Component/Default/SpriteRenderer.h"

/**
 * @brief 塗った面を表示するバー
 */
class  PaintMeshBar : public GameObject {

	// クラス定数の宣言 -------------------------------------------------
private:

	static constexpr float LAYER_DEPTH = 0.2f;

	// データメンバの宣言 -----------------------------------------------
private:

	SpriteRenderer* m_spriteRenderer = nullptr;	// スプラライト描画コンポーネント

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	PaintMeshBar();

	// デストラクタ
	~PaintMeshBar();

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
