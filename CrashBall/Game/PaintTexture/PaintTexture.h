/*****************************************************************//**
 * \file   PaintTexture.h
 * \brief  ペイントテクスチャ
 * 
 * \author 深沢拓矢
 * \date   November 2026
 *********************************************************************/

#pragma once

#include "Game/RenderTexture/MyRenderTexture.h"

#include "Game/ServiceLocator/IPaintTexture.h"

struct PaintCommand
{
	DirectX::SimpleMath::Vector2 position;
	DirectX::SimpleMath::Color color;
};

 /**
  * \brief ペイントテクスチャ
  */
class  PaintTexture : 
	public MyRenderTexture,
	public IPaintTexture
{

	// メンバ変数の宣言 -----------------------------------------------
private:

	std::vector<PaintCommand> m_paintCommands;

	ID3D11ShaderResourceView* m_inkSprite;
	float m_inkSpriteWidth;
	float m_inkSpriteHeight;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	PaintTexture(DXGI_FORMAT format);

	// デストラクタ
	~PaintTexture() = default;

	// 操作
public:

	// 描画命令の登録
	void RegisterRenderCommnad(
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Color& color) override;

	// 描画
	void Draw(ID3D11DeviceContext1* context, DirectX::SpriteBatch* spriteBatch);

	// 取得/設定
public:

	ID3D11ShaderResourceView* GetPaintTexture() const override
	{
		return GetShaderResourceView();
	}

	// スプライトの設定
	void SetInkSpirte(
		ID3D11ShaderResourceView* sprite,
		float width, float height)
	{
		m_inkSprite = sprite;
		m_inkSpriteWidth = width;
		m_inkSpriteHeight = height;
	}

	// 内部実装
private:

};
