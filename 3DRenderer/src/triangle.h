#pragma once
#include "vector.h"
#include <iostream>


struct face_t 
{
	int a;
	int b;
	int c;
};

struct triangle_t
{
	vec2_t points[3];
	float avgDepth;
};

void drawFilledTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void fillFlatBottom(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void fillFlatTop(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
