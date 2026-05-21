#pragma once

#include "Component.h"

/**
 * @brief 基底オブジェクト
 */
class  SpriteRenderer : public Component{

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	ID3D11ShaderResourceView* m_pSprite = nullptr;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	SpriteRenderer();

	// デストラクタ
	~SpriteRenderer();

	// 操作
public:

	//void Render(SpriteRendererManager* rendererManager, const RECT& rect);

	// 取得/設定
public:

	void SetSprite(ID3D11ShaderResourceView* pSprite);

	// 内部実装
private:

};
