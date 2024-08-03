#pragma once
#include "vector.h"
#include <iostream>
#include "texture.h"

struct face_t 
{
	int a;
	int b;
	int c;
	tex2_t aUV;
	tex2_t bUV;
	tex2_t cUV;

	uint32_t color;
};

struct triangle_t
{
	vec2_t points[3];
	uint32_t color;
	float avgDepth;
};

void drawFilledTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void fillFlatBottom(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void fillFlatTop(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void drawLine(int x0, int y0, int x1, int y1, uint32_t color);
