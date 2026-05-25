/*****************************************************************//**
 * \file   PrimitveRendererManager.h
 * \brief  プリミティブ描画管理クラス 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "Game/Interface/IPrimitiveRendererManager.h"
#include "Game/Common/Camera.h"

/**
 * @brief プリミティブ描画管理クラス
 */
class  PrimitiveRendererManager : public IPrimitiveRendererManager {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionNormalColor>> m_primitiveBatch;		// プリミティブバッチ

	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;		// ベーシックエフェクト

	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;	// 入力レイアウト

	std::vector<PrimitiveRenderCommand> m_renderCommand;		// 描画命令コンテナ


	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	PrimitiveRendererManager() = default;

	// デストラクタ
	~PrimitiveRendererManager() = default;

	// 操作
public:

	// リソースの生成
	void Create(
		ID3D11Device1* device,
		ID3D11DeviceContext1* context,
		DirectX::CommonStates* state
	);

	// 描画命令の登録
	void RegisterRenderCommand(
		D3D10_PRIMITIVE_TOPOLOGY topology,
		const std::vector<DirectX::VertexPositionNormalColor>& vertices
	) override;

	// 描画命令のクリア
	void ClearRenderCommand();

	// 描画
	void Render(
		ID3D11DeviceContext1* context,
		DirectX::CommonStates* state, 
		Camera* camera);


	// 取得/設定
public:

	// 射影行列の設定
	void SetProj(DirectX::SimpleMath::Matrix proj);

	// 内部実装
private:

};
