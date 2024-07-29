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

	// Loop all the scanlines from bottom to top
	for (int y = y2; y >= y0; y--) {
		drawLine(x_start, y, x_end, y, color);
		x_start -= inv_slope_1;
		x_end -= inv_slope_2;
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