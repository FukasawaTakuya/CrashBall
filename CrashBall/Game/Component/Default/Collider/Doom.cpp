/*****************************************************************//**
 * \file   Doom.cpp
 * \brief  内側に押し出す球
 *
 * \author 深沢拓矢
 * \date   September 2026
 *********************************************************************/

#include "pch.h"
#include "Doom.h"

using namespace DirectX;

RegisterComponent(Doom)

Doom::Doom(IGameObject* gameObject)
	: Collider(gameObject, ColliderType::Doom)
{
}
