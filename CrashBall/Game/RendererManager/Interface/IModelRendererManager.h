/*****************************************************************//**
 * \file   IModelRendererManager.h
 * \brief  モデル描画管理クラスのインターフェース 
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once

#include <Model.h>
#include <SimpleMath.h>
#include "Game/MyModel/MyModel.h"
#include "Game/Shader/Shader.h"

// 描画命令の登録用
struct ModelRenderCommand
{
	DirectX::Model* pModel;				// モデルのポインタ
	DirectX::SimpleMath::Matrix world;	// ワールド行列
};
// 描画命令の登録用
struct MyModelRenderCommand
{
	MyModel* pModel;					// モデルのポインタ
	Shader* vertexShader;				// 頂点シェーダ
	Shader* pixelShader;				// ピクセルシェーダ
	DirectX::SimpleMath::Matrix world;	// ワールド行列
};

/**
 * \brief モデル描画管理クラスのインターフェース
 */
class  IModelRendererManager {

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
	virtual void RegisterRenderCommand(
		DirectX::Model* model,
		const DirectX::SimpleMath::Matrix& world) = 0;

	// 描画命令の登録
	virtual void RegisterRenderCommand(
		MyModel* model,
		Shader* vertexShader,
		Shader* pixelShader,
		const DirectX::SimpleMath::Matrix& world) = 0;

	// 内部実装
private:

};
