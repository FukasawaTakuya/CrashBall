#pragma once
#include "Game/GameObject/GameObject.h"


/**
 * \brief 
 */
class  GameObjectFactory {

	using CreataFunc = GameObject*(*)(json*);

	// データメンバの宣言 -----------------------------------------------
private:

	std::vector<std::unique_ptr<GameObject>> m_gameObjects;

	// メンバ関数の宣言 -------------------------------------------------
	// コンストラクタ/デストラクタ
private:

	// コンストラクタ
	GameObjectFactory();

	// 複数生成の禁止
	GameObjectFactory(GameObjectFactory&) = delete;
	GameObjectFactory& operator=(GameObjectFactory&) = delete;

	// デストラクタ
	~GameObjectFactory() = default;

	// 操作
public:

	// 取得/設定
public:

	static GameObject* Create3DObject(json* data);

	// 内部実装
private:

	// インスタンスの取得
	static GameObjectFactory& GetInstance()
	{
		auto instance = GameObjectFactory();

		return instance;
	}

};
