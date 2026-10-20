/*****************************************************************//**
 * \file   SkyboxRenderManager.h
 * \brief  スカイボックス描画管理クラス
 * 
 * \author 深沢拓矢
 * \date   October 2026
 *********************************************************************/

#pragma once
#include "DX/SkyboxEffect.h"

// インターフェースの宣言
/**
 * \brief 描画命令登録インターフェース
 */
class ISkyboxRenderManager
{
public:

	// 描画命令の登録
	virtual	void RegisterRenderCommand() = 0;
};

/**
 * \brief キューブマップの設定インターフェース
 */
class ISkyboxManager
{
public:
	// キューブマップの設定
	virtual void SetCubeMap(ID3D11ShaderResourceView* cubemap) = 0;
};

 /**
  * \brief スカイボックス描画管理クラス
  */
class  SkyboxRenderManager 
	: public ISkyboxRenderManager
	, public ISkyboxManager
{

	// メンバ変数の宣言 -----------------------------------------------
private:

	std::unique_ptr<DirectX::GeometricPrimitive> m_sky;				// 描画用のジオメトリプリミティブ
	std::unique_ptr<SkyboxEffect>				 m_effect;			// スカイボックスエフェクト				
	Microsoft::WRL::ComPtr<ID3D11InputLayout>	 m_skyInputLayout;	// 入力レイアウト
	ID3D11ShaderResourceView*					 m_cubemap;			// キューブマップ

	bool m_isRender = false;	// 描画フラグ

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	SkyboxRenderManager();

	// デストラクタ
	~SkyboxRenderManager() = default;

	// 操作
public:

	// 描画命令の登録
	void RegisterRenderCommand() override;

	// 描画命令のクリア
	void ClearRenderCommand();

	// 描画
	void Render(
		ID3D11DeviceContext1* context,
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& proj);

	// スカイボックス作成
	void CreateSkybox(
		ID3D11Device1* device,
		ID3D11DeviceContext1* context);

	// 取得/設定
public:

	// キューブマップの設定
	void SetCubeMap(ID3D11ShaderResourceView* cubemap) override
	{
		m_cubemap = cubemap;
		if (cubemap != nullptr)
		{
			m_cubemap = cubemap;
			m_effect->SetTexture(m_cubemap);
		}
	}

	// 内部実装
private:

};
