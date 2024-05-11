#pragma once



struct vec2_t
{
	float x, y;
};

struct vec3_t
{
	float x, y, z;
};

float vec2Length(vec2_t v);
float vec3Length(vec3_t v);
vec3_t vec3RotateX(vec3_t point, float angle);
vec3_t vec3RotateY(vec3_t point, float angle);
vec3_t vec3RotateZ(vec3_t point, float angle);
