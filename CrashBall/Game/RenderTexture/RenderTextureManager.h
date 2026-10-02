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
	MyRenderTexture* CreateRenderTexture(DXGI_FORMAT format) override;

	// レンダーテクスチャの削除
	void DeleteRenderTexture(MyRenderTexture* renderTexture) override;

	// 取得/設定
public:

	// レンダーテクスチャリストの取得
	std::vector<std::unique_ptr<MyRenderTexture>>* GetRenderTextureList()
	{
		return &m_renderTextureList;
	}

	// 内部実装
private:

};
