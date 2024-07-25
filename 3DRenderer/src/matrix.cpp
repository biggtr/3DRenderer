#include "matrix.h"
#include "vector.h"
#include <iostream>

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


mat4_t makeScaleMatrix(float xValue, float yValue, float zValue)
{
	//making the scale matrix so we can use it to scale objects in future 
	mat4_t scaleMatrix = mat4Identity();
	scaleMatrix.m[0][0] = xValue;
	scaleMatrix.m[1][1] = yValue;
	scaleMatrix.m[2][2] = zValue;

	return scaleMatrix;
}

mat4_t makeTranslationMatrix(float xValue, float yValue, float zValue)
{
	mat4_t translationMatrix = mat4Identity();
	translationMatrix.m[0][3] = xValue;
	translationMatrix.m[1][3] = yValue;
	translationMatrix.m[2][3] = zValue;
	return translationMatrix;
}

mat4_t makeRotationMatrixInX(float angel)
{
	mat4_t xRotationMatrix = mat4Identity();
	xRotationMatrix.m[1][1] = std::cos(angel);
	xRotationMatrix.m[1][2] = -std::sin(angel);
	xRotationMatrix.m[2][1] = sin(angel);
	xRotationMatrix.m[2][2] = std::cos(angel);
	return xRotationMatrix;
}

vec4_t multiplyMatrixVector(mat4_t matrix, vec4_t vector)
{
	vec4_t resultingVector;
	resultingVector.x = matrix.m[0][0] * vector.x + matrix.m[0][1] * vector.y + matrix.m[0][2] * vector.z + matrix.m[0][3] * vector.w;
	resultingVector.y = matrix.m[1][0] * vector.x + matrix.m[1][1] * vector.y + matrix.m[1][2] * vector.z + matrix.m[1][3] * vector.w;
	resultingVector.z = matrix.m[2][0] * vector.x + matrix.m[2][1] * vector.y + matrix.m[2][2] * vector.z + matrix.m[2][3] * vector.w;
	resultingVector.w = matrix.m[3][0] * vector.x + matrix.m[3][1] * vector.y + matrix.m[3][2] * vector.z + matrix.m[3][3] * vector.w;
	return resultingVector;
}

