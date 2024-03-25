#pragma once
#include "vector.h"


struct face_t 
{
	int a;
	int b;
	int c;
};

struct triangle_t
{
	vec2_t points[3];
};