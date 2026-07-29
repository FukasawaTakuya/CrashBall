/*****************************************************************//**
 * \file   ModelRenderer.h
 * \brief  モデル描画クラス 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"
#include "Game/ResourceManager/Interface/IModelManager.h"
#include "Game/RendererManager/Interface/IModelRendererManager.h"

#include "Game/Component/Default/Physics/Transform.h"

 /**
 * @brief 基底オブジェクト
 */
class  ModelRenderer : public Component {

	// インスペクター編集GUIをフレンド化
	friend class ObjectInspectorGui;

	// データメンバの宣言 -----------------------------------------------
private:

	DirectX::Model* m_pModel = nullptr;	// モデルのポインタ

	Transform* m_transform = nullptr;	// トランスフォームのキャッシュ

	std::string m_modelKey;	// モデルのキー

	// プロパティの設定
	BeginProperty()
		AddProperty(m_modelKey, PropertyType::String)
	EndProperty()

	// コンポーネント名の設定
	SetCompName("ModelRenderer")

	
	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// デフォルトコンストラクタ
	ModelRenderer() = default;

	// コンストラクタ
	ModelRenderer(IGameObject* gameObject);

	// コピーコンストラクタ
	ModelRenderer(
		IGameObject* gameObject,
		const ModelRenderer& other);

	// デストラクタ
	~ModelRenderer();

	// 操作
public:

	// 描画
	void Render(IModelRendererManager* rendererManager);

	// 取得/設定
public:

	// モデルの取得 
	DirectX::Model* GetModel() const
	{
		return m_pModel;
	}
	
	// モデルのキーの取得
	std::string GetModelKey() const
	{
		return m_modelKey;
	}

	// モデルの設定
	void SetModel(IModelManager* modelManager)
	{
		m_pModel = modelManager->GetModel(m_modelKey);
	}

	// ディフーズカラーの設定
	void SetDiffuseColor(const DirectX::SimpleMath::Color& color);

	// 内部実装
private:

	// プロパティの取得
	virtual const std::vector<PropertyInfo>& GetProperties() const override
	{
		return m_properties;
	}

	// コンポーネント名の取得
	virtual std::string GetCompName() const override
	{
		return m_compName;
	}

	// JsonConvert
private:

	friend void from_json(const nlohmann::json& j, ModelRenderer& modelRenderer);
	friend void to_json(nlohmann::json& j, const ModelRenderer& modelRenderer);

public:

	// 演算子オーバーロード
	void operator=(ModelRenderer renderer)
	{
		m_modelKey = renderer.m_modelKey;
	}
};
