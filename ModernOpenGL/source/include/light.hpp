#pragma once

#include "basicMath.hpp"

namespace LowRenderer
{
	struct Light
	{
		vec4 diffuseColor;
		vec4 ambientColor;
		vec4 specularColor;
	};

}