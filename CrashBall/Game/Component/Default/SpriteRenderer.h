/*****************************************************************//**
 * \file   SpriteRenderer.h
 * \brief  スプライト描画コンポーネント
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once

#include "Component.h"
#include "Game/Interface/ISpriteRendererManager.h"

/**
 * @brief スプライト描画管理コンポーネント
 */
class  SpriteRenderer : public Component{

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	ID3D11ShaderResourceView* m_pSprite = nullptr;	// スプライトのポインタ

	int m_orderInLayer = 0;		// 描画順

	DirectX::XMVECTORF32 m_color = DirectX::Colors::White;	// 色

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	SpriteRenderer(IGameObject* gameObject);

	// デストラクタ
	~SpriteRenderer();

	// 操作
public:

	// 描画
	void Render(ISpriteRendererManager* rendererManager, const RECT& rect);

	// 取得/設定
public:

	// スプライトの設定
	void SetSprite(ID3D11ShaderResourceView* pSprite)
	{
		m_pSprite = pSprite;
	}

	// 描画順の設定
	void SetOrderInLayer(int orderInLayer)
	{
		m_orderInLayer = orderInLayer;
	}

	// 色の設定
	void SetColor(const DirectX::XMVECTORF32& color)
	{
		m_color = color;
	}

	// 内部実装
private:

};
