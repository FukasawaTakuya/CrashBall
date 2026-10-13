/*****************************************************************//**
 * \file   OrthgraphicCamera.h
 * \brief  正投影カメラ
 *
 * \author 深沢拓矢
 * \date   October 2026
 *********************************************************************/

#include "pch.h"
#include "OrthgraphicCamera.h"

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