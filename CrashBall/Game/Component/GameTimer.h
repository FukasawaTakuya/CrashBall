#pragma once

#include "Game/Component/Default/Component.h"
#include "Default/Renderer/TextRenderer.h"

/**
 * @brief ゲームタイマー
 */
class  GameTimer : public Component {


	// メンバ変数の宣言 -------------------------------------------------
private:
	float m_timer = 0.0f;	// タイマー

	// パラメータ
private:
	float m_gameTime = 0.0f;			// ゲーム時間
	TextRenderer* m_timeText = nullptr;	// 時間表示用のテキスト

	// プロパティの設定
	BeginProperty()
		AddProperty(m_gameTime, PropertyType::Float)
	EndProperty()

		// コンポーネント名の設定
	SetCompName("GameTimer")

		// メンバ関数の宣言 -------------------------------------------------
		// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	GameTimer(IGameObject* gameObject) : Component(gameObject) {}

	// デストラクタ
	~GameTimer() = default;

	// 操作
public:

	// 開始処理
	virtual void Awake() override;

	// 初期処理
	virtual void Start(const GameContext& gameContext) override;

	// 更新
	virtual void Update(const GameContext& gameContext) override;

	// 取得/設定
public:

	float GetTimer() const
	{
		return m_timer;
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