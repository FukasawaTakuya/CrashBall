#pragma once

#include "Game/Component/Default/Component.h"

/**
 * @brief
 */
class  ComputShaderController : public Component {

	// メンバ変数の宣言 -------------------------------------------------

	std::unique_ptr<Shader> m_computShader;	// コンピュートシェーダー

	std::string m_computShaderKey;

	DirectX::SimpleMath::Vector3 m_groupNum;	// スレッドグループ数

	// プロパティの設定
	BeginProperty()
		AddProperty(m_computShaderKey, PropertyType::String)
		AddProperty(m_groupNum, PropertyType::Vector3)
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
		m_computShader = std::make_unique<Shader>();
		m_computShader->SetShader(resourceContext.shaderManager->GetShaderInfo(m_computShaderKey));
	}

	// 取得/設定
public:

	// シェーダーの取得
	Shader* GetShader() const
	{
		return m_computShader.get();
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