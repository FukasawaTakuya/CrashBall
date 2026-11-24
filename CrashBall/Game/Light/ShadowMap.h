#pragma once

#include "Game/RenderTexture/MyRenderTexture.h"

/**
 * \brief シャドウマップ
 */
class  ShadowMap : public MyRenderTexture {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:



	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	ShadowMap();

	// デストラクタ
	~ShadowMap();

	// 操作
public:

	// 描画開始
	void Begin(ID3D11DeviceContext1* context);

	// 取得/設定
public:

	// 内部実装
private:

};
