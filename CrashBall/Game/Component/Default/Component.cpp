#include "pch.h"
#include "Component.h"

/**
 * \brief コンストラクタ
 * 
 * \param gameObject コンポーネントを所有しているゲームオブジェクト
 */
Component::Component(IGameObject* gameObject)
	: m_gameObject(gameObject) 
{
}