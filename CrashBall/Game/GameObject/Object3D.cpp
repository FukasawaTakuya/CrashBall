/*****************************************************************//**
 * \file   Object3D.cpp
 * \brief  3Dオブジェクト
 * 
 * \author 深沢拓矢
 * \date   June 2026
 *********************************************************************/

#include "pch.h"
#include "Object3D.h"
#include "Game/Component/Default/Physics/Transform.h"

/**
 * \brief コンストラクタ
 * 
 */
Object3D::Object3D()
{
	m_transform =  AddComponent<Transform>();
	m_modelRenderer = AddComponent<ModelRenderer>();
}

/**
 * \brief デストラクタ
 * 
 */
Object3D::~Object3D()
{
}

/**
 * \brief 初期化
 * 
 */
void Object3D::Initialize()
{
}

/**
 * \brief 更新
 * 
 * \param gameContext ゲーム用のコンテキスト
 */
void Object3D::Update(const GameContext& gameContext)
{
	
}

/**
 * \brief 描画
 * 
 * \param renderContext 描画用のコンテキスト
 */
void Object3D::Render(const RenderContext& renderContext)
{
	m_modelRenderer->Render(renderContext.modelRendererManager);
}

/**
 * \brief 終了処理
 * 
 */
void Object3D::Finalize()
{
}

void Object3D::SaveParam()
{
}

void Object3D::SaveInitParam()
{
}

void Object3D::ReloadJson()
{
}
