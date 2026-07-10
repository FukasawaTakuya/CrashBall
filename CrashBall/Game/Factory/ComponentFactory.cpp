#include "pch.h"
#include "ComponentFactory.h"

#include "Game/GameObject/GameObject.h"

#include "Game/Component/Default/Physics/Transform.h"

/**
 * \brief コンストラクタ
 * 
 */
ComponentFactory::ComponentFactory()
{

}

Component* ComponentFactory::Create(json data, GameObject* gameObject)
{
	auto& instance = GetInstance();

	if (instance.m_createComp.find(data["compName"]) != instance.m_createComp.end())
	{
		return instance.m_createComp[data["compName"]](data);
	}
}

Component* ComponentFactory::CreateTransform(GameObject* gameObject, json data)
{
	return Create<Transform>(gameObject, data);
}
