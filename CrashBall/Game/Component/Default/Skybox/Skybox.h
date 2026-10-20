/*****************************************************************//**
 * \file   Skybox.h
 * \brief  スカイボックス
 * 
 * \author 深沢拓矢
 * \date   October 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"
#include "GeometricPrimitive.h"
#include "DX/SkyboxEffect.h"
#include "Game/Component/Camera/Camera.h"

/**
 * @brief スカイボックス
 */
class  Skybox : public Component {

	// メンバ変数の宣言 -------------------------------------------------

	std::string m_skyboxKey;

	// プロパティの設定
	BeginProperty()
		AddProperty(m_skyboxKey, PropertyType::String)
	EndProperty()

	// コンポーネント名の設定
	SetCompName("Skybox")

		// メンバ関数の宣言 -------------------------------------------------
		// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	Skybox(IGameObject* gameObject);

	// デストラクタ
	~Skybox() = default;

	// 操作
public:

	// アタッチ時の処理
	void Awake() override;
	// 開始処理
	void Start(const GameContext& gameContext) override;
	// 更新
	void Update(const GameContext& gameContext) override;
	// 描画
	void Render(const RenderContext& renderContext) override;

	// デバイス依存のリソースの設定
	void SetDeviceResource(const ResourceContext& resourceContext) override;

	// 編集時に実行する関数
	void EditedFunc(const ResourceContext& resourceContext);

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