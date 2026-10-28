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

#include "Game/Shader/Shader.h"

 /**
 * @brief モデル描画コンポーネント
 */
class  ModelRenderer : public Component {

	// メンバ変数の宣言 -----------------------------------------------
private:

	MyModel* m_pModel		= nullptr;	// モデルのポインタ

	Transform* m_transform = nullptr;	// トランスフォームのキャッシュ

	std::string m_modelKey;	// モデルのキー

	std::unique_ptr<Shader> m_vertexShader;	// 頂点シェーダ
	std::unique_ptr<Shader> m_pixelShader;	// ピクセルシェーダ
	std::string m_vertexShaderKey = "Basic_VS";	// 頂点シェーダのキー
	std::string m_pixelShaderKey  = "Basic_PS";	// ピクセルシェーダのキー

	// プロパティの設定
	BeginProperty()
		AddProperty(m_modelKey,			PropertyType::String)
		AddProperty(m_vertexShaderKey,	PropertyType::String)
		AddProperty(m_pixelShaderKey,	PropertyType::String)
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
		// モデルの設定
		m_pModel = resourceContext.modelManager->GetModel(m_modelKey);

		// シェーダの設定
		m_vertexShader = std::make_unique<Shader>();
		m_pixelShader = std::make_unique<Shader>();
		m_vertexShader->SetShader(resourceContext.shaderManager->GetShaderInfo(m_vertexShaderKey));
		m_pixelShader->SetShader(resourceContext.shaderManager->GetShaderInfo(m_pixelShaderKey));
	}

	// 取得/設定
public:
	
	// モデルのキーの取得
	std::string GetModelKey() const
	{
		return m_modelKey;
	}

	// ディフーズカラーの取得
	DirectX::SimpleMath::Color GetDiffuseColor() const
	{
		return DirectX::SimpleMath::Color{ 1,1,1,1 };
	}
	// アンビエントカラーの取得
	DirectX::SimpleMath::Color GetAmbientColor() const
	{
		return DirectX::SimpleMath::Color{ 1,1,1,1 };
	}

	// ディフーズカラーの設定
	void SetDiffuseColor(const DirectX::SimpleMath::Color& color)
	{
		ApplyDiffuseColor();
	}

	// アンビエントライトカラーの設定
	void SetAmbientColor(const DirectX::SimpleMath::Color& color)
	{
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
