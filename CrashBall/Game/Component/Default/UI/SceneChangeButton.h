#pragma once

#include "Game/Component/Default/Component.h"
#include "Game/Component/Default/UI/ButtonController.h"

/**
 * @brief 
 */
class  SceneChangeButton : public ButtonController {

	// クラス定数の宣言 -------------------------------------------------
public:

	// データメンバの宣言 -----------------------------------------------
private:

	std::string m_nextSceneName;

	// プロパティの設定
	BeginProperty()
		AddProperty(m_nextSceneName, PropertyType::String)
	EndProperty()

	// コンポーネント名の設定
	SetCompName("ButtonController")



	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
public:

	// コンストラクタ
	SceneChangeButton(IGameObject* gameObject);

	// デストラクタ
	~SceneChangeButton();

	// 操作
public:

	// アタッチ時の処理
	void Awake() override;

	// 更新
	void Update(const GameContext& gameContext) override;

	// 取得/設定
public:

	// 内部実装
private:

};
