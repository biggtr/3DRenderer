#pragma once
#include "vector.h"
#include <iostream>


struct Light
{
	vec3_t direction;
};
extern Light light;

uint32_t light_apply_intensity(uint32_t original_color, float percentage_factor);