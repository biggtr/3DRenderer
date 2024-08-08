#include "triangle.h"
#include "display.h"
void fillFlatBottom(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
	// Find the two slopes (two triangle legs)
	float inv_slope_1 = (float)(x1 - x0) / (y1 - y0);
	float inv_slope_2 = (float)(x2 - x0) / (y2 - y0);

	// Start x_start and x_end from the top vertex (x0,y0)
	float x_start = x0;
	float x_end = x0;

	// Loop all the scanlines from top to bottom
	for (int y = y0; y <= y2; y++) {
		drawLine(x_start, y, x_end, y, color);
		x_start += inv_slope_1;
		x_end += inv_slope_2;
	}
}
void fillFlatTop(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
	// Find the two slopes (two triangle legs)
	float inv_slope_1 = (float)(x2 - x0) / (y2 - y0);
	float inv_slope_2 = (float)(x2 - x1) / (y2 - y1);

	// Start x_start and x_end from the bottom vertex (x2,y2)
	float x_start = x2;
	float x_end = x2;

	// Loop all the scan lines from bottom to top
	for (int y = y2; y >= y0; y--) {
		drawLine(x_start, y, x_end, y, color);
		x_start -= inv_slope_1;
		x_end -= inv_slope_2;
	}
}

void drawTexturedTriangle(int x0, int y0, float u0, float v0, int x1, int y1, float u1, float v1, int x2, int y2, float u2, float v2, uint32_t* texture)
{
	//ugly sorting to make sure that y0 < y1 < y2
	if (y0 > y1)
	{
		std::swap(y0, y1);
		std::swap(x0, x1);
		std::swap(u0, u1);
		std::swap(v0, v1);

	}
	if (y1 > y2)
	{
		std::swap(y1, y2);
		std::swap(x1, x2);
		std::swap(u1, u2);
		std::swap(v1, v2);


	}
	if (y0 > y1)
	{
		std::swap(y0, y1);
		std::swap(x0, x1);
		std::swap(u0, u1);
		std::swap(v0, v1);

	}
	//Render the upper part of the triangle (flat bottom)
	float leftLegSlope{}, rightLegSlope{};
	if (y1 - y0 != 0)
		float leftLegSlope = (float)(x1 - x2) / std::abs(y1 - y0);
	if (y2 - y0 != 0)
		float rightLegSlope = (float)(x2 - x0) / std::abs(y2 - y0);
	for (int y = y0; y <= y1; y++) 
	{
		int x_start = x1 + (y - y1) * leftLegSlope;
		int x_end = x0 + (y - y0) * rightLegSlope;

		if (x_end < x_start) {
			std::swap(x_start, x_end); // swap if x_start is to the right of x_end
		}
		for (int x = x_start; x < x_end; x++)
		{
			drawPixel(x, y, 0xFFFFFFFF);
		}
	}
}
void drawFilledTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
	//ugly sorting solution 
	if (y0 > y1)
	{
		std::swap(y0, y1);
		std::swap(x0, x1);
	}
	if (y1 > y2)
	{
		std::swap(y1, y2);
		std::swap(x1, x2);
	}
	if (y0 > y1)
	{
		std::swap(y0, y1);
		std::swap(x0, x1);
	}


	//check if we only have a flat bottom y1 == y2 if we do we draw only flat bottom
	if (y1 == y2)
	{
		fillFlatBottom(x0, y0, x1, y1, x2, y2, color);
	}
	//check if we only have a flat top y0 == y1 if we do we draw only flat top
	else if (y0 == y1)
	{
		
		fillFlatTop(x1, y1, x0, y0, x2, y2, color);

	}
	else
	{
		// Calculate the new vertex (Mx,My) using triangle similarity
		int My = y1;
		int Mx = (((x2 - x0) * (y1 - y0)) / (y2 - y0)) + x0;

		fillFlatBottom(x0, y0, x1, y1, Mx, My, color);
		fillFlatTop(x1, y1, Mx, My, x2, y2, color);
	}
}

void drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
	drawLine(x0, y0, x1, y1, color);
	drawLine(x1, y1, x2, y2, color);
	drawLine(x2, y2, x0, y0, color);

}