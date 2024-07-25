#pragma once


//forward declaration
struct vec4_t;

struct mat4_t 
{
	float m[4][4];
};

mat4_t mat4Identity();
mat4_t makeScaleMatrix(float xValue, float yValue, float zValue);
mat4_t makeTranslationMatrix(float xValue, float yValue, float zValue);
mat4_t makeRotationMatrixInX(float angle);
mat4_t makeRotationMatrixInY(float angle);
mat4_t makeRotationMatrixInZ(float angle);

vec4_t multiplyMatrixVector(mat4_t matrix, vec4_t vector);
