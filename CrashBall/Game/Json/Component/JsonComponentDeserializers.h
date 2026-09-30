#pragma once

#include "Game/Geometory/Triangle.h"
#include "Game/Component/Default/Component.h"
#include "Game/GameObject/GameObject.h"

// PropertyInfoへ変換
void from_json(const ordered_json& j, PropertyInfo& property);

// Componentへ変換
void from_json(const ordered_json& j, Component& component);

// GameObjectへ変換
void from_json(const ordered_json& j, GameObject& gameObject);

// Triangleへ変換
void from_json(const json& j, Triangle& triangle);