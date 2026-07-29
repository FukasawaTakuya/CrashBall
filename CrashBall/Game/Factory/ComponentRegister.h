#pragma once
#include <string>
#include "ComponentFactory.h"

template <typename Comp>
class ComponentRegister
{
public:

	// コンストラクタ
	ComponentRegister(const std::string& compName)
	{
		ComponentFactory::RegistComponentFunc(
			compName,
			[](IGameObject* gameObject)
			{
				return std::move(std::make_unique<Comp>(gameObject));
			}
		);
	}
};
