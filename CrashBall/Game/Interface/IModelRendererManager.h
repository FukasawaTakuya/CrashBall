/*****************************************************************//**
 * \file   IModelRendererManager.h
 * \brief  モデル描画管理クラスのインターフェースに関するヘッダーファイル
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once

#include <Model.h>
#include <SimpleMath.h>

// 描画命令の登録用
struct ModelDrawCommand
{
	DirectX::Model* pModel;				// モデルのポインタ
	DirectX::SimpleMath::Matrix world;	// ワールド行列
};


/**
 * @brief モデル描画管理クラスのインターフェース
 */
class  IModelRendererManager {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:



	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	IModelRendererManager() = default;

	// デストラクタ
	virtual ~IModelRendererManager() = default;

	// 操作
public:

	// 取得/設定
public:
	// 描画命令の登録
	virtual void RegisterDrawCommand(const ModelDrawCommand& drawCommand) = 0;


	// 内部実装
private:

};
