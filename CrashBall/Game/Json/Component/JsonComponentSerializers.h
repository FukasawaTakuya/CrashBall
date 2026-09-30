#pragma once

#include "Game/Json/Enum/JsonEnumSerializers.h"

#include "Game/Component/Default/Component.h"
#include "Game/GameObject/GameObject.h"

// PropertyInfoから変換
void to_json(ordered_json& j, const PropertyInfo& property);

// Componentから変換
void to_json(ordered_json& j, const Component& component);

// GameObjectから変換
void to_json(ordered_json& j, const GameObject& gameObject);
