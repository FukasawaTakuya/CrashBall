/*****************************************************************//**
 * \file   ComputShaderController.h
 * \brief  コンピュートシェーダー操作
 * 
 * \author 深沢拓矢
 * \date   November 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"

struct ComputShader
{
	std::unique_ptr<Shader> computShader;	// コンピュートシェーダー
	std::string computShaderKey;
	DirectX::SimpleMath::Vector3 groupNum;	// スレッドグループ数
	bool updateEnable = true;				// 毎フレーム更新
	bool updateTrigger = false;				// 更新トリガー
};

/**
 * @brief コンピュートシェーダー操作
 */
class  ComputShaderController : public Component {

	// メンバ変数の宣言 -------------------------------------------------

	ComputShader m_shaders[3];

	// プロパティの設定
	BeginProperty()
		AddProperty(m_shaders[0].computShaderKey, PropertyType::String)
		AddProperty(m_shaders[0].groupNum, PropertyType::Vector3)
		AddProperty(m_shaders[0].updateEnable, PropertyType::Bool)
		AddProperty(m_shaders[1].computShaderKey, PropertyType::String)
		AddProperty(m_shaders[1].groupNum, PropertyType::Vector3)
		AddProperty(m_shaders[1].updateEnable, PropertyType::Bool)
		AddProperty(m_shaders[2].computShaderKey, PropertyType::String)
		AddProperty(m_shaders[2].groupNum, PropertyType::Vector3)
		AddProperty(m_shaders[2].updateEnable, PropertyType::Bool)
	EndProperty()

	// コンポーネント名の設定
	SetCompName("ComputShaderController")

		// メンバ関数の宣言 -------------------------------------------------
		// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	ComputShaderController(IGameObject* gameObject);

	// デストラクタ
	~ComputShaderController() = default;

	// 操作
public:

	// アタッチ時の処理
	void Awake() override;
	// 開始処理
	void Start(const GameContext& gameContext) override;
	// 更新
	void Update(const GameContext& gameContext) override;

	// リソースの設定
	void SetDeviceResource(const ResourceContext& resourceContext) override 
	{
		for (int i = 0; i < 3; i++)
		{
			m_shaders[i].computShader = std::make_unique<Shader>();
			m_shaders[i].computShader->SetShader(resourceContext.
				shaderManager->GetShaderInfo(m_shaders[i].computShaderKey));
		}
	}

	// 更新トリガーを起こす
	void EnableUpdateTrigger(const std::string& shaderName)
	{
		for (int i = 0; i < 3; i++)
		{
			if (m_shaders[i].computShaderKey == shaderName)
				m_shaders[i].updateTrigger = true;;
		}
	}

	// 取得/設定
public:

	// シェーダーの取得
	Shader* GetShader(const std::string& shaderName) const
	{
		for (int i = 0; i < 3; i++)
		{
			if (m_shaders[i].computShaderKey == shaderName)
				return m_shaders[i].computShader.get();
		}
		return nullptr;
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