/*****************************************************************//**
 * \file   MyRenderTexture.h
 * \brief  レンダーテキスチャ生成クラス
 * 
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#pragma once
#include "DeviceResources.h"
#include "DX/RenderTexture.h"
#include "Game/Component/Camera/Camera.h"

/**
 * \brief レンダーテキスチャ生成クラス
 */
class  MyRenderTexture {

	// メンバ変数の宣言 -----------------------------------------------
private:

	// レンダーテクスチャ
	std::unique_ptr<DX::RenderTexture> m_renderTexture;

	// ビューポート
	D3D11_VIEWPORT m_viewport{};

	// カメラ
	Camera* m_camera = nullptr;

	// ウィンドウ全体を描画するか
	bool m_isWindow = true;

	float m_width;
	float m_height;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	MyRenderTexture(DXGI_FORMAT format);

	// デストラクタ
	~MyRenderTexture() = default;

	// 操作
public:

	// 描画開始
	void Begin(
		ID3D11DeviceContext1* context,
		ID3D11DepthStencilView* dsv);

	// 描画終了
	void End(
		ID3D11DeviceContext1* context,
		ID3D11DepthStencilView* dsv,
		ID3D11RenderTargetView* const backRtv);

	// CreateWindowSizeDependentResourcesで呼ぶ用
	void SetWindowSizeDependend(const RECT& rect);

	// ====================== RenderTextureのラッパー ======================= //

	void SetDevice(ID3D11Device* device);

	void SizeResources(size_t width, size_t height);

	void ReleaseDevice();

	void SetWindow(const RECT& rect);

	ID3D11Texture2D* GetRenderTarget() const noexcept { return m_renderTexture->GetRenderTarget(); }
	ID3D11RenderTargetView* GetRenderTargetView() const noexcept { return m_renderTexture->GetRenderTargetView(); }
	ID3D11ShaderResourceView* GetShaderResourceView() const noexcept { return m_renderTexture->GetShaderResourceView(); }
	ID3D11DepthStencilView* GetDepthStencilView() const noexcept { return m_renderTexture->GetDepthStencilView(); }

	// 取得/設定
public:

	// ビューポートの取得
	D3D11_VIEWPORT GetViewPort() const { return m_viewport; }

	// カメラの取得
	Camera* GetCamera() { return m_camera; }

	// 横幅の取得
	float GetWidth() const { return m_viewport.Width; }

	// 縦幅の取得
	float GetHeight() const { return m_viewport.Height; }

	// カメラの設定
	void SetCamera(Camera* camera) { m_camera = camera; }

	// 内部実装
private:

};
