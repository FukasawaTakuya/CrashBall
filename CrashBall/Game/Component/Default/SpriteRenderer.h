/*****************************************************************//**
 * \file   SpriteRenderer.h
 * \brief  スプライト描画コンポーネント
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once

#include "Component.h"
#include "RectTransform.h"
#include "Game/Interface/ISpriteRendererManager.h"

/**
 * @brief スプライト描画管理コンポーネント
 */
class  SpriteRenderer : public Component {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	ID3D11ShaderResourceView* m_pSprite = nullptr;	// スプライトのポインタ

	float m_layerDepth = 0.0f;		// 描画順

	DirectX::XMVECTORF32 m_color = DirectX::Colors::White;	// 色

	float m_width = 0.0f;	// 横幅
	float m_height = 0.0f;	// 縦幅

	DirectX::SimpleMath::Vector2 m_spriteScale = DirectX::SimpleMath::Vector2::One;	// スプライトのスケール

	RectTransform* m_rectTransform = nullptr;	// トランスフォームのキャッシュ

	float m_valueX = 1.0f;
	float m_valueY = 1.0f;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	SpriteRenderer(IGameObject* gameObject);

	// デストラクタ
	~SpriteRenderer();

	// 操作
public:

	void Render(ISpriteRendererManager* rendererManager);

	// 取得/設定
public:

	// スプライトの設定
	void SetSprite(ID3D11ShaderResourceView* pSprite)
	{
		// スプライトの設定
		m_pSprite = pSprite;

		// スプライトのサイズを求める
		ID3D11Resource* resource;
		m_pSprite->GetResource(&resource);
		ID3D11Texture2D* texture = static_cast<ID3D11Texture2D*>(resource);
		D3D11_TEXTURE2D_DESC desc;
		texture->GetDesc(&desc);
		m_width = desc.Width;
		m_height = desc.Height;
	}

	// 描画順の設定
	void SetLayerDepth(float layerDepth)
	{
		m_layerDepth = layerDepth;
	}

	// 色の設定
	void SetColor(const DirectX::XMVECTORF32& color)
	{
		m_color = color;
	}

	// スプライトのスケールの設定
	void SetSpriteScale(float spriteScale)
	{
		SetSpriteScale(DirectX::SimpleMath::Vector2::One * spriteScale);
	}

	// スプライトのスケールの設定
	void SetSpriteScale(const DirectX::SimpleMath::Vector2& spriteScale)
	{
		m_spriteScale = spriteScale;
	}

	void SetVelueX(float valueX)
	{
		m_valueX = valueX;
	}

	// 内部実装
private:

};
