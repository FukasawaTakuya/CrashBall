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

	std::vector<PrimitiveDrawCommand> m_drawCommand;			// 命令コンテナ


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
	void CreateResource(
		ID3D11Device1* device,
		ID3D11DeviceContext1* context,
		DirectX::CommonStates* state
	);

	// 描画命令の登録
	void RegisterDrawCommand(const PrimitiveDrawCommand& drawCommand) override;

	// 描画命令のクリア
	void ClearCommandList();

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
