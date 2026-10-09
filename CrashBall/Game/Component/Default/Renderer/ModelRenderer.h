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

	DirectX::SimpleMath::Color m_diffuseColor = { 1.0f, 1.0f, 1.0f, 1.0f }; // ディフーズカラー
	DirectX::SimpleMath::Color m_ambientColor = { 0.6f, 0.6f, 0.6f, 0.6f }; // アンビエントライトカラー

	std::string m_modelKey;	// モデルのキー

	// プロパティの設定
	BeginProperty()
		AddProperty(m_modelKey, PropertyType::String)
		AddProperty(m_diffuseColor, PropertyType::Color)
		AddProperty(m_ambientColor, PropertyType::Color)
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
	void SetDeviceResource(const ResourceContext& resourceContext) override
	{
		m_pModel = resourceContext.modelManager->GetModel(m_modelKey);

		if (m_pModel != nullptr)
		{
			m_pModel->UpdateEffects(
				[&](DirectX::IEffect* effect) {

					DirectX::BasicEffect* basic = dynamic_cast<DirectX::BasicEffect*>(effect);
					if (basic)
					{
						basic->SetAmbientLightColor(m_ambientColor);
						basic->SetDiffuseColor(m_diffuseColor);
					}
				});
		}
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

	// ディフーズカラーの取得
	DirectX::SimpleMath::Color GetDiffuseColor() const
	{
		return m_diffuseColor;
	}
	// アンビエントカラーの取得
	DirectX::SimpleMath::Color GetAmbientColor() const
	{
		return m_ambientColor;
	}

	// モデルの設定
	void SetModel(IModelManager* modelManager)
	{
	}

	// ディフーズカラーの設定
	void SetDiffuseColor(const DirectX::SimpleMath::Color& color)
	{
		m_diffuseColor = color;
		ApplyDiffuseColor();
	}

	// アンビエントライトカラーの設定
	void SetAmbientColor(const DirectX::SimpleMath::Color& color)
	{
		m_ambientColor = color;
		ApplyAmbientLight();
	}

	// 内部実装
private:

	// アンビエントライトの適用
	void ApplyAmbientLight();

	// ディフーズカラーの適用
	void ApplyDiffuseColor();

	// 変更されたとき実行する関数
	void EditedFunc(const ResourceContext& resourceContext) override
	{
		SetDeviceResource(resourceContext);
	}

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
