/*****************************************************************//**
 * \file   RenderTextureManager.h
 * \brief  レンダーテクスチャ管理クラス
 * 
 * \author 深沢拓矢
 * \date   October 2026
 *********************************************************************/

#pragma once

#include "MyRenderTexture.h"
#include "Game/ServiceLocator/IRenderTargetManager.h"

 /**
  * \brief レンダーテクスチャ管理クラス
  */
class  RenderTextureMangaer : public IRenderTargetManager {

	// メンバ変数の宣言 -----------------------------------------------
private:

	// レンダーテクスチャリスト
	std::vector <std::unique_ptr<MyRenderTexture>> m_renderTextureList;

	// レンダーテクスチャ初期化用
	DXGI_FORMAT m_format;
	ID3D11Device1* m_device;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	RenderTextureMangaer(DXGI_FORMAT format);

	// デストラクタ
	~RenderTextureMangaer() = default;

	// 操作
public:

	// レンダーテクスチャの作成
	MyRenderTexture* CreateRenderTexture() override;

	// レンダーテクスチャの削除
	void DeleteRenderTexture(MyRenderTexture* renderTexture) override;

	// CreateWindowSizeDependentResourcesで呼ぶ用
	void SetWindowSizeDependend(const RECT& rect);

	// 取得/設定
public:

	// レンダーテクスチャリストの取得
	std::vector<std::unique_ptr<MyRenderTexture>>* GetRenderTextureList()
	{
		return &m_renderTextureList;
	}

	// フォーマットの設定
	void SetFormat(DXGI_FORMAT format)
	{
		m_format = format;
	}

	// デバイスの設定
	void SetDevice(ID3D11Device1* device)
	{
		m_device = device;
		for (auto& renderTexture : m_renderTextureList)
		{
			renderTexture->SetDevice(device);
		}
	}


	// 内部実装
private:

};
