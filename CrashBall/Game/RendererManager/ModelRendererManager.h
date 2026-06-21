/*****************************************************************//**
 * \file   ModelRendererManager.h
 * \brief  モデル描画管理クラス 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "Game/Interface/IModelRendererManager.h"

/**
 * @brief モデル描画管理クラス
 */
class  ModelRendererManager : public IModelRendererManager {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	std::vector<ModelRenderCommand> m_renderCommand;	// 描画命令コンテナ


	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	ModelRendererManager() = default;

	// デストラクタ
	~ModelRendererManager() = default;

	// 操作
public:

	// 描画命令の登録
	void RegisterRenderCommand(
		DirectX::Model* model,
		const DirectX::SimpleMath::Matrix& world
	) override;

	// 描画命令のクリア
	void ClearRenderCommand();

	// 描画
	void Render(
		ID3D11DeviceContext1* context,
		DirectX::CommonStates* state,
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& proj
		);


	// 取得/設定
public:

	// 内部実装
private:

};
