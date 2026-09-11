#include "pch.h"
#include "GameColor.h"

RegisterComponent(GameColor)

GameColor::GameColor(IGameObject* gameObject)
	: ScriptableComponent(gameObject)
{
	SetScirptableTypeid(typeid(GameColor));
}
