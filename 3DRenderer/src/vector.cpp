#include <math.h>
#include "vector.h"



vec3_t vec3_rotate_x(vec3_t point, float angle)
{
	vec3_t rotated_vector =
	{
		point.x,
		point.y* cos(angle) - point.z * sin(angle),
		point.y* sin(angle) + point.z * cos(angle),

	};
	return rotated_vector;
}
	

vec3_t vec3_rotate_y(vec3_t point,float angle)
{
	vec3_t rotated_vector =
	{
		point.x * cos(angle) - point.z * sin(angle),
		point.y,
		point.x * sin(angle) + point.z * cos(angle),
	};
	return rotated_vector;
}

vec3_t vec3_rotate_z(vec3_t point, float angle)
{			
	vec3_t rotated_vector =
	{
		point.x * cos(angle) - point.y * sin(angle),
		point.x * sin(angle) + point.y * cos(angle),
		point.z
	};
	return rotated_vector;
}

