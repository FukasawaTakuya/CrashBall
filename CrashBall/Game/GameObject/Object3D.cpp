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

Object3D::~Object3D()
{
}

void Object3D::Initialize()
{
}

void Object3D::Update(const GameContext& gameContext)
{
	
}

void Object3D::Render(const RenderContext& renderContext)
{
	m_modelRenderer->Render(
		renderContext.modelRendererManager,
		m_transform->GetWorld());
}

void Object3D::Finalize()
{
}
