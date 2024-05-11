#include "vector.h"
#include <math.h>



float vec2Length(vec2_t v)
{
	
	return sqrt((v.x*v.x) + (v.y * v.y));
}

float vec2Length(vec3_t v)
{

	return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z) );
}

vec3_t vec3RotateX(vec3_t point, float angle)
{
	vec3_t rotated_vector =
	{
		point.x,
		point.y* cos(angle) - point.z * sin(angle),
		point.y* sin(angle) + point.z * cos(angle),

	};
	return rotated_vector;
}
	

vec3_t vec3RotateY(vec3_t point,float angle)
{
	vec3_t rotated_vector =
	{
		point.x * cos(angle) - point.z * sin(angle),
		point.y,
		point.x * sin(angle) + point.z * cos(angle),
	};
	return rotated_vector;
}

vec3_t vec3RotateZ(vec3_t point, float angle)
{			
	vec3_t rotated_vector =
	{
		point.x * cos(angle) - point.y * sin(angle),
		point.x * sin(angle) + point.y * cos(angle),
		point.z
	};
	return rotated_vector;
}

