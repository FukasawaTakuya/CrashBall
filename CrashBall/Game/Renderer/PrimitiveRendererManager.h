/*****************************************************************//**
 * \file   PrimitveRendererManager.h
 * \brief  プリミティブ描画管理クラスに関するヘッダーファイル
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

// 多重インクルードの防止 =====================================================
#pragma once

// ヘッダファイルの読み込み ===================================================
#include "Game/Common/Camera.h"
// クラスの前方宣言 ===================================================

// 構造体の前方宣言 ===================================================

// 描画命令用
struct PrimitiveDrawCommand
{
	D3D10_PRIMITIVE_TOPOLOGY topology;
	std::vector<DirectX::VertexPositionNormalColor> vertices;
};


// クラスの定義 ===============================================================
/**
 * @brief 基底オブジェクト
 */
class  PrimitiveRendererManager {

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
private:

	// コンストラクタ
	PrimitiveRendererManager() = default;
	PrimitiveRendererManager(PrimitiveRendererManager&) = delete;
	PrimitiveRendererManager& operator= (const PrimitiveRendererManager&) = delete;

	// デストラクタ
	~PrimitiveRendererManager() = default;

	// 操作
public:
	// インスタンスの取得
	static PrimitiveRendererManager& Instance() {
		static PrimitiveRendererManager instance;
		return instance;
	}

	// リソースの生成
	void CreateResource(
		ID3D11Device1* device,
		ID3D11DeviceContext1* context,
		DirectX::CommonStates* state,
		DirectX::SimpleMath::Matrix projMat
	);

	// 描画命令の登録
	void RegisterDrawCommand(PrimitiveDrawCommand drawCommand);

	// 描画命令のクリア
	void ClearCommandList();

	// 描画
	void Draw(Camera* pCamera);


	// 取得/設定
public:

	// 内部実装
private:

};
