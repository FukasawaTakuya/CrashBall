/*****************************************************************//**
 * \file   ModelRendererManager.h
 * \brief  モデル描画管理クラス 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "Game/RendererManager/Interface/IModelRendererManager.h"

#include "Game/RenderTexture/MyRenderTexture.h"

/**
 * @brief モデル描画管理クラス
 */
class  ModelRendererManager : public IModelRendererManager {

	// データメンバの宣言 -----------------------------------------------
private:

	std::vector<ModelRenderCommand> m_renderCommand;	// 描画命令コンテナ

	std::vector<ModelRenderCommand> m_maskRenderCommand;// マスクへの描画命令コンテナ

	// 深度書き込み用ピクセルシェーダー
	std::unique_ptr<Shader> m_depthPS;

	MyRenderTexture* m_mask;		// マスク

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
		MyModel* model,
		const DirectX::SimpleMath::Color& diffuseColor,
		Shader* vertexShader,
		Shader* pixelShader,
		const DirectX::SimpleMath::Matrix& world) override;

	// マスクへの描画命令の登録
	void RegisterMaskRenderCommand(
		MyModel* model,
		Shader* vertexShader,
		Shader* pixelShader,
		const DirectX::SimpleMath::Matrix& world) override;

	// 描画命令のクリア
	void ClearRenderCommand();

	// 描画
	void Render(
		ID3D11DeviceContext1* context,
		DirectX::CommonStates* state,
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& proj,
		const DirectX::SimpleMath::Vector3& lightDire,
		const DirectX::SimpleMath::Matrix& lightView,
		const DirectX::SimpleMath::Matrix& lightProj,
		ID3D11ShaderResourceView* shadowMap);

	// 深度のみの描画
	void RenderDepth(
		ID3D11DeviceContext1* context,
		DirectX::CommonStates* state,
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& proj);

	// 描画
	void RenderMask(
		ID3D11DeviceContext1* context,
		DirectX::CommonStates* state,
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& proj);

	void CreateMask();

	// 取得/設定
public:

	MyRenderTexture* GetMask() { return m_mask; }

	// シェーダーの設定
	void SetShader(ShaderInfo* shaderInfo)
	{
		m_depthPS = std::make_unique<Shader>();
		m_depthPS->SetShader(shaderInfo);
	}

	// 内部実装
private:

};
