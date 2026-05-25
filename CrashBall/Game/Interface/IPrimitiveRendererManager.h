/*****************************************************************//**
 * \file   IPrimitiveRendererManager.h
 * \brief  プリミティブ描画管理クラスのインターフェース 
 * 
 * \author 深沢拓矢
 * \date   May 2026
 *********************************************************************/

#pragma once
#include <d3d10.h>
#include <DirectXColors.h>
#include <vector>

 // 描画命令用
struct PrimitiveRenderCommand
{
	D3D10_PRIMITIVE_TOPOLOGY topology;
	std::vector<DirectX::VertexPositionNormalColor> vertices;
};


/**
 * @brief プリミティブ描画管理クラスのインターフェース
 */
class  IPrimitiveRendererManager {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	IPrimitiveRendererManager() = default;

	// デストラクタ
	virtual ~IPrimitiveRendererManager() = default;

	// 操作
public:

	// 描画命令の登録
	virtual void RegisterRenderCommand(
		D3D10_PRIMITIVE_TOPOLOGY topology,
		const std::vector<DirectX::VertexPositionNormalColor>& vertices
	) = 0;

	// 取得/設定
public:

	// 内部実装
private:

};
