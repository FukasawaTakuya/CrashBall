/*****************************************************************//**
 * \file   ModelRenderer.h
 * \brief  モデル描画クラス 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"
#include "Game/RendererManager/Interface/IModelRendererManager.h"

#include "Game/Component/Default/Physics/Transform.h"

 /**
 * @brief 基底オブジェクト
 */
class  ModelRenderer : public Component {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	DirectX::Model* m_pModel = nullptr;	// モデルのポインタ

	Transform* m_transform = nullptr;	// トランスフォームのキャッシュ

	std::string m_modelKey;	// モデルのキー
	
	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	ModelRenderer(IGameObject* gameObject);

	// コピーコンストラクタ
	ModelRenderer(
		IGameObject* gameObject,
		const std::string& modelKey);


	// デストラクタ
	~ModelRenderer();

	// 操作
public:

	// 描画
	void Render(IModelRendererManager* rendererManager);

	// 取得/設定
public:

	DirectX::Model* GetModel()
	{
		return m_pModel;
	}
	
	// モデルの設定
	void SetModel(DirectX::Model* pModel)
	{
		m_pModel = pModel;
	}

	// ディフーズカラーの設定
	void SetDiffuseColor(const DirectX::XMVECTORF32& color);

	// 内部実装
private:

	// JsonConvert
private:
	friend void from_json(const json& j, ModelRenderer& modelRenderer);
	friend void to_json(json& j, const ModelRenderer& modelRenderer);
};
