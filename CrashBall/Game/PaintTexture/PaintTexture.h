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
#include "Game/ResourceManager/ShaderManager.h"

struct PaintCommand
{
	DirectX::SimpleMath::Vector2 position;
	DirectX::SimpleMath::Color color;
	int id;
};

 /**
  * \brief ペイントテクスチャ
  */
class  PaintTexture : 
	public MyRenderTexture,
	public IPaintTexture
{
private:

	static constexpr float TEXTURE_SIZE = 4096.0f * 2.0f;
	static constexpr float INKSPRITE_SCALE = 0.08f * 2.0f;

	const std::string PIXEL_SHADER_NAME = "PaintTexture_PS";

	// メンバ変数の宣言 -----------------------------------------------
private:

	ID3D11DeviceContext1* m_context;	// デバイスコンテキスト

	std::vector<PaintCommand> m_paintCommands;	// ペイント命令

	ID3D11ShaderResourceView* m_inkSprite;	// インク用スプライト
	float m_inkSpriteWidth;
	float m_inkSpriteHeight;

	std::unique_ptr<MyRenderTexture> m_paintTimeTex;	// ペイント時間打ち込み用テクスチャ

	std::unique_ptr<Shader> m_pixelShader;	// ピクセルシェーダー

	Microsoft::WRL::ComPtr<ID3D11BlendState> m_paintBlendState;

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
		const DirectX::SimpleMath::Color& color,
		int id) override;

	// ペイントのクリア
	void ClearPaint() override;

	// 描画
	void Draw(
		DirectX::SpriteBatch* spriteBatch,
		DirectX::CommonStates* states);

	// ブレンドステートの作成
	void CreateBlendState(
		DirectX::CommonStates* states,
		ID3D11Device1* device);

	// 取得/設定
public:

	// ペイントテクスチャの取得
	ID3D11ShaderResourceView* GetPaintTexture() const override
	{
		return GetShaderResourceView();
	}

	// ペイント時間テクスチャの取得
	ID3D11ShaderResourceView* GetPaintTimeTex() const override
	{
		return m_paintTimeTex->GetShaderResourceView();
	}

	// レンダーターゲットの取得
	ID3D11Texture2D* GetRenderTarget() const override { return m_renderTexture->GetRenderTarget(); }

	// ペイント時間テクスチャのレンダーターゲットの取得
	ID3D11Texture2D* GetPaintTimeRenderTarget() const override { return m_paintTimeTex->GetRenderTarget(); }

	// スプライトの設定
	void SetInkSpirte(
		ID3D11ShaderResourceView* sprite,
		float width, float height)
	{
		m_inkSprite = sprite;
		m_inkSpriteWidth = width;
		m_inkSpriteHeight = height;
	}

	// デバイスの設定
	void SetDevice(ID3D11Device* device)
	{
		MyRenderTexture::SetDevice(device);
		m_paintTimeTex->SetDevice(device);
	}

	// コンテキストの設定
	void SetContext(ID3D11DeviceContext1* context)
	{
		m_context = context;
	}

	// シェーダーのセット
	void SetShader(ShaderManager* shaderManager)
	{
		m_pixelShader->SetShader(shaderManager->GetShaderInfo(PIXEL_SHADER_NAME));
	}

	// サイズの設定
	void SetSize();

	// 内部実装
private:
};
