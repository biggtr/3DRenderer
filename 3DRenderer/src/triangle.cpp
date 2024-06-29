#include "triangle.h"

void fillFlatBottom(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{

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
	int Mx= (y1 - y0) * (x2 - x0) / (y2 - y0) + x0;
	int My = y1;

	fillFlatBottom(x0,y0,x1,y1,Mx,My, TODO);
	fillFlatTop(x1,y1,Mx,My,x2,y2);
}
