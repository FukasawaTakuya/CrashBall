/*****************************************************************//**
 * \file   MiniMap.h
 * \brief  ミニマップ
 * 
 * \author 深沢拓矢
 * \date   October 2026
 *********************************************************************/

#pragma once

#include "Game/Component/Default/Component.h"
#include "Game/Component/Camera/Camera.h"
#include "Game/Component/Default/Renderer/SpriteRenderer.h"
#include "Game/RenderTexture/MyRenderTexture.h"

/**
 * @brief ミニマップ
 */
class  MiniMap : public Component {

	// メンバ変数の宣言 -------------------------------------------------

	Camera* m_pSubCamera = nullptr;		// ミニマップ描画用カメラ

	float m_size;	// ミニマップのサイズ

	// レンダーテクスチャのキャッシュ
	MyRenderTexture* m_renderTextrue = nullptr;

	// コンポーネントのキャッシュ
	SpriteRenderer* m_spriteRenderer = nullptr;

	// プロパティの設定
	BeginProperty()
		AddProperty(m_pSubCamera, PropertyType::Component)
		AddProperty(m_size, PropertyType::Float)
	EndProperty()

	// コンポーネント名の設定
	SetCompName("MiniMap")

		// メンバ関数の宣言 -------------------------------------------------
		// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	MiniMap(IGameObject* gameObject);

	// デストラクタ
	~MiniMap();

	// 操作
public:

	// アタッチ時の処理
	void Awake() override;
	// 開始処理
	void Start(const GameContext& gameContext) override;
	// 更新
	void Update(const GameContext& gameContext) override;
	// 終了処理
	void Finalize() override;

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