/*****************************************************************//**
 * \file   IRenderTargetManager.h
 * \brief  レンダーテクスチャ管理クラスのインターフェース
 * 
 * \author 深沢拓矢
 * \date   October 2026
 *********************************************************************/

#pragma once
#include "Service.h"
#include "Game/RenderTexture/MyRenderTexture.h"
#include "dxgiformat.h"

 /**
  * \brief レンダーテクスチャ管理クラスのインターフェース
  */
class  IRenderTargetManager : public Service {

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	IRenderTargetManager() = default;

	// デストラクタ
	~IRenderTargetManager() = default;

	// 操作
public:

	// レンダーテクスチャの作成
	virtual MyRenderTexture* CreateRenderTexture() = 0;

	// レンダーテクスチャの削除
	virtual void DeleteRenderTexture(MyRenderTexture* renderTexture) = 0;


	// 取得/設定
public:

	// 内部実装
private:

};
