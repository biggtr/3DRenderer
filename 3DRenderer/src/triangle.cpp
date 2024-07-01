#include "triangle.h"
#include "display.h"
void fillFlatBottom(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
	float leftSideSlope = (float)(x1 - x0) / (y1 - y0);
	float rightSideSlope = (float)(x2 - x1) / (y2 - y1);

	int xStart{ x0 }, xEnd{ x0};

	for (int height = y0; height <= y2; height++)
	{
		drawLine(xStart, height, xEnd, height, color);
		xStart += leftSideSlope;
		xEnd += rightSideSlope;
	}
}
void fillFlatTop(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{

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

	//calcualting midpoint of triangle 
	int xMidPoint= (y1 - y0) * (x2 - x0) / (y2 - y0) + x0;
	int yMidPoint = y1;

	fillFlatBottom(x0,y0,x1,y1,xMidPoint,yMidPoint,color);
	//fillFlatTop(x1,y1,xMidPoint,yMidPoint,x2,y2,color);
}
