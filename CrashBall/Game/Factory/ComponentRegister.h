#pragma once
#include <string>
#include "ComponentFactory.h"

template <typename Comp>
class ComponetRegister
{
public:

	// コンストラクタ
	ComponetRegister(const std::string& compName)
	{
		ComponentFactory::RegistComponentFunc(
			compName,
			[]()
			{
				return std::make_unique<Comp>();
			}
		)
	}
};
