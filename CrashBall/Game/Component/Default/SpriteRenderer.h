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

 // 切り取りの基準位置
enum class FillOrigin
{
	CenterHorizon = 0,
	CenterVertical,
	Left,
	Top,
	Right,
	Bottom,
	OriginNum,
};

// 切り取りの基準位置を決めるためのオフセット
const DirectX::SimpleMath::Vector4 FillOriginOffeset[static_cast<int>(FillOrigin::OriginNum)]
{
	DirectX::SimpleMath::Vector4(-0.5f,  0.0f, 0.5f, 0.0f),	// CenterHorizon
	DirectX::SimpleMath::Vector4( 0.0f, -0.5f, 0.0f, 0.5f),	// CenterVartical
	DirectX::SimpleMath::Vector4( 0.0f,  0.0f, 1.0f, 0.0f),	// Left
	DirectX::SimpleMath::Vector4( 0.0f,  0.0f, 0.0f, 1.0f),	// Top
	DirectX::SimpleMath::Vector4(-1.0f,  0.0f, 0.0f, 0.0f),	// Right
	DirectX::SimpleMath::Vector4( 0.0f, -1.0f, 0.0f, 0.0f),	// Bottom
};

// 切り取りの基準位置を決めるためのもとになる切り取り領域
const DirectX::SimpleMath::Vector4 SourceBaseRECT[static_cast<int>(FillOrigin::OriginNum)]
{
	DirectX::SimpleMath::Vector4(0.5f, 0.0f, 0.5f, 1.0f),	// CenterHorizon
	DirectX::SimpleMath::Vector4(0.0f, 0.5f, 1.0f, 0.5f),	// CenterVartical
	DirectX::SimpleMath::Vector4(0.0f, 0.0f, 0.0f, 1.0f),	// Left
	DirectX::SimpleMath::Vector4(0.0f, 0.0f, 1.0f, 0.0f),	// Top
	DirectX::SimpleMath::Vector4(1.0f, 0.0f, 1.0f, 1.0f),	// Right
	DirectX::SimpleMath::Vector4(0.0f, 1.0f, 1.0f, 1.0f),	// Bottom
};

/**
 * @brief スプライト描画コンポーネント
 */
class  SpriteRenderer : public Component {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	ID3D11ShaderResourceView* m_pSprite = nullptr;					// スプライトのポインタ
	DirectX::XMVECTORF32 m_color = DirectX::Colors::White;			// 色
	float m_width = 0.0f;											// 横幅
	float m_height = 0.0f;											// 縦幅
	DirectX::SimpleMath::Vector2 m_spriteScale = { 1.0f, 1.0f };	// スプライトのスケール
	float m_layerDepth = 0.0f;										// 描画順
	RectTransform* m_rectTransform = nullptr;						// トランスフォームのキャッシュ
	FillOrigin m_fillOrigin = FillOrigin::Left;						// 切り取りの起点
	float m_fillAmount = 1.0f;										// 切り取り量

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
	void Render(ISpriteRendererManager* rendererManager);

	// 取得/設定
public:

	// 横幅の取得
	float GetWidth() const
	{
		// 切り取りが横方向の場合
		if (static_cast<int>(m_fillOrigin) % 2 == 0)
		{
			return m_width * m_spriteScale.x * m_fillAmount;
		}
		else
		{
			return m_width * m_spriteScale.x;
		}
	}

	// 縦幅の取得
	float GetHeight() const
	{
		// 切り取りが縦方向の場合
		if (static_cast<int>(m_fillOrigin) % 2 == 1)
		{
			return m_height * m_spriteScale.y * m_fillAmount;
		}
		else
		{
			return m_height * m_spriteScale.y;
		}

	}

	// 切り取り量を取得
	float GetFillAmount() const
	{
		return m_fillAmount;
	}

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

	// 切り取り量を設定
	void SetFillAmount(float fillAmount)
	{
		m_fillAmount = fillAmount;
	}

	// 切り取りする際の起点を設定
	void SetFillOrigin(FillOrigin fillOrigin)
	{
		m_fillOrigin = fillOrigin;
	}

	// 内部実装
private:

};
