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

	// 毎フレーム描画しないレンダーテクスチャリスト
	std::vector <std::unique_ptr<MyRenderTexture>> m_customRenderTextureList;

	ID3D11Device1* m_device;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	RenderTextureMangaer();

	// デストラクタ
	~RenderTextureMangaer() = default;

	// 操作
public:

	// レンダーテクスチャの作成
	MyRenderTexture* CreateRenderTexture(DXGI_FORMAT format, bool isDepth) override;

	// レンダーテクスチャの作成
	MyRenderTexture* CreateCustomRenderTexture(DXGI_FORMAT format, bool isDepth) override;

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


	// デバイスの設定
	void SetDevice(ID3D11Device1* device)
	{
		m_device = device;
		for (auto& renderTexture : m_renderTextureList)
		{
			renderTexture->SetDevice(device);
		}
		for (auto& renderTexture : m_customRenderTextureList)
		{
			renderTexture->SetDevice(device);
		}
	}


	// 内部実装
private:

};
