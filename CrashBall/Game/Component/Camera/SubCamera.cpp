#include "pch.h"
#include "SubCamera.h"

RegisterComponent(OrthgraphicCamera)

using namespace DirectX;

/**
 * \brief コンストラクタ
 * 
 * \param gameObejct コンポーネントを所有するゲームオブジェクト
 * \return 
 */
OrthgraphicCamera::OrthgraphicCamera(IGameObject* gameObejct)
	: Camera(gameObejct)
{
	m_baseTypeid = typeid(Camera);
}