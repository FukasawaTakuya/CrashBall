/*****************************************************************//**
 * \file   SpriteRenderer.h
 * \brief  スプライト描画コンポーネント
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"
#include "Game/Component/Default/Physics/RectTransform.h"

#include "Game/RendererManager/Interface/ISpriteRendererManager.h"
#include "Game/ResourceManager/Interface/ISpriteManager.h"

 // 切り取りの基準位置
enum class FillOrigin
{
	Center = 0,
	CenterHorizon,
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
	DirectX::SimpleMath::Vector4(-0.5f, -0.5f, 0.5f, 0.5f),	// Center
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
	DirectX::SimpleMath::Vector4(0.5f, 0.5f, 0.5f, 0.5f),	// Center
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

	ID3D11ShaderResourceView* m_pSprite		   = nullptr;							// スプライトのポインタ
	DirectX::SimpleMath::Color m_color		   = { 1.0f, 1.0f, 1.0f, 1.0f };		// 色
	float m_width							   = 0.0f;								// 横幅
	float m_height							   = 0.0f;								// 縦幅
	DirectX::SimpleMath::Vector2 m_spriteScale = DirectX::SimpleMath::Vector2::One;	// スプライトのスケール
	float m_layerDepth						   = 0.0f;								// 描画順
	FillOrigin m_fillOrigin					   = FillOrigin::Left;					// 切り取りの起点
	float m_fillAmount						   = 1.0f;								// 切り取り量
	DirectX::SpriteEffects m_spriteEffects = DirectX::SpriteEffects::SpriteEffects_None;// 反転するか

	std::string m_spriteKey;	// スプライトのキー

	RectTransform* m_rectTransform = nullptr;	// トランスフォームのキャッシュ

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	SpriteRenderer(IGameObject* gameObject);

	// コピーコンストラクタ
	SpriteRenderer(
		IGameObject* gamebject,
		SpriteRenderer* spriteRenderer
	);

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
		if (static_cast<int>(m_fillOrigin) % 2 == 1)
		{
			return m_width * m_spriteScale.x * m_rectTransform->GetWorldScale().x * m_fillAmount;
		}
		else
		{
			return m_width * m_spriteScale.x * m_rectTransform->GetWorldScale().x;
		}
	}

	// 縦幅の取得
	float GetHeight() const
	{
		// 切り取りが縦方向の場合
		if (static_cast<int>(m_fillOrigin) % 2 == 0)
		{
			return m_height * m_spriteScale.y * m_rectTransform->GetWorldScale().y * m_fillAmount;
		}
		else
		{
			return m_height * m_spriteScale.y * m_rectTransform->GetWorldScale().y;
		}

	}

	// 切り取り量を取得
	float GetFillAmount() const
	{
		return m_fillAmount;
	}

	std::string GetSpriteKey() const
	{
		return m_spriteKey;
	}

	// スプライトの設定
	void SetSprite(ISpriteManager* spriteManager)
	{
		const SpriteInfo* spriteInfo = spriteManager->GetSpriteInfo(m_spriteKey);

		if (spriteInfo != nullptr)
		{
			m_pSprite = spriteInfo->sprite.Get();
			m_width = spriteInfo->width;
			m_height = spriteInfo->height;
		}
	}

	// 描画順の設定
	void SetLayerDepth(float layerDepth)
	{
		m_layerDepth = std::clamp(layerDepth, 0.0f, 1.0f);
	}

	// 色の設定
	void SetColor(const DirectX::XMVECTORF32& color)
	{
		m_color = color;
	}

	// スプライトのスケールの設定
	void SetSpriteScale(const DirectX::SimpleMath::Vector2& spriteScale)
	{
		m_spriteScale = spriteScale;
	}

	// スプライトのスケールの設定
	void SetSpriteScale(float x, float y)
	{
		m_spriteScale.x = x;
		m_spriteScale.y = y;
	}

	// スプライトのスケールの設定
	void SetSpriteScale(float spriteScale)
	{
		m_spriteScale = DirectX::SimpleMath::Vector2::One * spriteScale;
	}

	// 切り取り量を設定
	void SetFillAmount(float fillAmount)
	{
		m_fillAmount = std::clamp(fillAmount, 0.0f, 1.0f);
	}

	// 切り取りする際の起点を設定
	void SetFillOrigin(FillOrigin fillOrigin)
	{
		m_fillOrigin = fillOrigin;
	}

	// 画像の反転の設定
	void SetSpriteEffects(DirectX::SpriteEffects spriteEffects)
	{
		m_spriteEffects = spriteEffects;
	}

	// 透明度の設定
	void SetAlpha(float alpha)
	{
		m_color.w = std::clamp(alpha, 0.0f, 1.0f);;
	}

	void SetSpriteKey(const std::string& spriteKey)
	{
		m_spriteKey = spriteKey;
	}

	// 内部実装
private:

	// JsonConvert
private:

	friend void from_json(const json& j, SpriteRenderer& spriteRenderer);
	friend void to_json(json& j, const SpriteRenderer& spriteRenderer);
};
