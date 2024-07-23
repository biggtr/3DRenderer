#include "matrix.h"



mat4_t mat4Identity()
{
	mat4_t identityMatrix;
	
	identityMatrix = { {
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1},

	} };
	return identityMatrix;
}


mat4_t scaleMatrix(float xValue, float yValue, float zValue)
{
	//making the scale matrix so we can use it to scale objects in future 
	mat4_t scaleMatrix = mat4Identity();
	scaleMatrix.m[0][0] = xValue;
	scaleMatrix.m[1][1] = yValue;
	scaleMatrix.m[2][2] = zValue;

	return scaleMatrix;
}

