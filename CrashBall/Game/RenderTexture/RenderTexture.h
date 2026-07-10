/*****************************************************************//**
 * \file   RenderTexture.h
 * \brief  レンダーテキスチャ生成クラス
 * 
 * \author 深沢拓矢
 * \date   July 2026
 *********************************************************************/

#pragma once
#include "DeviceResources.h"

/**
 * \brief レンダーテキスチャ生成クラス
 */
class  RenderTexture {

	// データメンバの宣言 -----------------------------------------------
private:

	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_texture;

	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_rtv;	// レンダーターゲット

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_srv;	// テクスチャ

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	RenderTexture();

	// デストラクタ
	~RenderTexture() = default;

	// 操作
public:

	// 
	void Create(DX::DeviceResources* deviceResources);

	// 描画開始
	void Begin(
		ID3D11DeviceContext1* context,
		ID3D11DepthStencilView* dsv);

	// 描画終了
	void End(
		ID3D11DeviceContext1* context,
		ID3D11DepthStencilView* dsv,
		ID3D11RenderTargetView* const backRtv);

	// 取得/設定
public:

	ID3D11ShaderResourceView* GetRenderTexture()
	{
		return m_srv.Get();
	}

	// 内部実装
private:

};
