/*****************************************************************//**
 * \file   ModelRenderer.h
 * \brief  モデル描画コンポーネント 
 * 
 * \author 深沢拓矢
 * \date   April 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"

#include "Game/Context/RenderContext.h"
#include "Game/Context/ResourceContext.h"
#include "Game/Component/Default/Physics/Transform.h"


 /**
 * @brief モデル描画コンポーネント
 */
class  ModelRenderer : public Component {

	// メンバ変数の宣言 -----------------------------------------------
private:

	DirectX::Model* m_pModel = nullptr;	// モデルのポインタ

	Transform* m_transform = nullptr;	// トランスフォームのキャッシュ

	DirectX::SimpleMath::Color m_diffuseColor = {1.0f, 1.0f, 1.0f, 1.0f}; // ディフーズカラー

	std::string m_modelKey;	// モデルのキー

	// プロパティの設定
	BeginProperty()
		AddProperty(m_modelKey, PropertyType::String)
		AddProperty(m_diffuseColor, PropertyType::Color)
	EndProperty()

	// コンポーネント名の設定
	SetCompName("ModelRenderer")

	
	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	ModelRenderer(IGameObject* gameObject);

	// デストラクタ
	~ModelRenderer() = default;

	// 操作
public:

	// アタッチ時の処理
	void Awake() override;

	// 描画
	void Render(const RenderContext& renderContext) override;

	// リソースの設定
	void SetResource(const ResourceContext& resourceContext) override
	{
		m_pModel = resourceContext.modelManager->GetModel(m_modelKey);

		m_pModel->UpdateEffects(
			[&](DirectX::IEffect* effect) {

				DirectX::BasicEffect* basic = dynamic_cast<DirectX::BasicEffect*>(effect);
				if (basic)
				{
					basic->SetDiffuseColor(m_diffuseColor);
				}
			});
	}

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
	}

	// ディフーズカラーの設定
	void SetDiffuseColor(const DirectX::SimpleMath::Color& color)
	{
		m_diffuseColor = color;
	}

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
};
