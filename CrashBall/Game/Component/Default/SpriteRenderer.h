#pragma once

#include "Component.h"
#include "Game/Interface/ISpriteRendererManager.h"

/**
 * @brief 基底オブジェクト
 */
class  SpriteRenderer : public Component{

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	ID3D11ShaderResourceView* m_pSprite = nullptr;
	int m_orderInLayer = 0;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	SpriteRenderer(IGameObject* owner);

	// デストラクタ
	~SpriteRenderer();

	// 操作
public:

	void Render(ISpriteRendererManager* rendererManager, const RECT& rect);

	// 取得/設定
public:

	void SetSprite(ID3D11ShaderResourceView* pSprite);

	void SetOrderInLayer(int orderInLayer)
	{
		m_orderInLayer = orderInLayer;
	}

	// 内部実装
private:

};
