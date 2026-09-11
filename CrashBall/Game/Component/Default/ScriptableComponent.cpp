#include "pch.h"
#include "ScriptableComponent.h"

using namespace DirectX;

RegisterComponent(ScriptableComponent)

/**
 * \brief コンストラクタ
 * 
 * \param gameObject コンポーネントを所有するゲームオブジェクト
 */
ScriptableComponent::ScriptableComponent(IGameObject* gameObject)
	: Component(gameObject)
	, m_scriptableTypeid(typeid(void*))
{
}

/**
 * \brief デストラクタ
 * 
 */
ScriptableComponent::~ScriptableComponent()
{
}
