#pragma once

#include "Game/Component/Default/Component.h"
#include "ModelRenderer.h"

/**
 * @brief
 */
class  MaskRenderer : public Component {

	// メンバ変数の宣言 -------------------------------------------------

	Transform* m_transform;
	ModelRenderer* m_modelRender;

	// プロパティの設定
	BeginProperty()
	EndProperty()

	// コンポーネント名の設定
	SetCompName("MaskRenderer")

		// メンバ関数の宣言 -------------------------------------------------
		// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	MaskRenderer(IGameObject* gameObject);

	// デストラクタ
	~MaskRenderer() = default;

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