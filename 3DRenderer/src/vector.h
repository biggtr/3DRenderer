#pragma once



struct vec2_t
{
	float x;
	float y;
};

struct vec3_t
{
	float x;
	float y;
	float z;
};


vec3_t vec3_rotate_x(vec3_t point, float angle);
vec3_t vec3_rotate_y(vec3_t point, float angle);
vec3_t vec3_rotate_z(vec3_t point, float angle);
