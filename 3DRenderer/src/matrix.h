#pragma once


struct mat4_t 
{
	float m[4][4];
};

mat4_t mat4Identity();
mat4_t scaleMatrix(float xValue, float yValue, float zValue);