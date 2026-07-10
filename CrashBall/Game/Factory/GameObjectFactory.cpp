#include "pch.h"
#include "GameObjectFactory.h"

#include "ComponentFactory.h"
#include "Game/GameObject/Object3D.h"

/**
 * \brief コンストラクタ
 * 
 */
GameObjectFactory::GameObjectFactory()
{
}

/**
 * \brief 3Dオブジェクトの生成
 * 
 * \param data jsonデータ
 * \return オブジェクトのポインタ
 */
GameObject* GameObjectFactory::Create3DObject(json* data)
{
	auto gameObject = std::make_unique<Object3D>();

	auto pGameObject = gameObject.get();

	for (json& comp : (*data)["Components"])
	{
		ComponentFactory::Create(comp, pGameObject);
	}

	GetInstance().m_gameObjects.push_back(std::move(gameObject));

	return pGameObject;
}
