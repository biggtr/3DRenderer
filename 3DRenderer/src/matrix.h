#pragma once


//forward declaration
struct vec4_t;

struct mat4_t 
{
	float m[4][4];
};

mat4_t mat4Identity();
mat4_t makeScaleMatrix(float xValue, float yValue, float zValue);
vec4_t multiplyMatrixVector(mat4_t matrix, vec4_t vector);