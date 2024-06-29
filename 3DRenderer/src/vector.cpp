#include "vector.h"
#include <iostream>

//////////////////////////////////////////////////////////////////////////
//Implementation of Vector 2D functions
//////////////////////////////////////////////////////////////////////////
float vec2Length(vec2_t v)
{
	
	return std::sqrt((v.x*v.x) + (v.y * v.y));
}

vec2_t vec2Addition(vec2_t v1, vec2_t v2)
{
	vec2_t newVec2 = { (v1.x + v2.x),(v1.y + v2.y) };
	return newVec2;
}
vec2_t vec2Subtraction(vec2_t v1, vec2_t v2)
{
	vec2_t newVec2 = { (v1.x - v2.x),(v1.y - v2.y) };
	return newVec2;
}



vec2_t vec2Multiplication(vec2_t v, float factor)
{
	vec2_t newVec2 = { v.x * factor,v.y * factor };
	return newVec2;
}
vec2_t vec2Division(vec2_t v, float factor)
{
	vec2_t newVec2 = { v.x / factor,v.y / factor };
	return newVec2;
}


float vec2DotProduct(vec2_t firstVector, vec2_t SecondVector)
{
	return (firstVector.x * SecondVector.x) + (firstVector.y * SecondVector.y);
}

//////////////////////////////////////////////////////////////////////////
//Implementation of Vector 3D functions
//////////////////////////////////////////////////////////////////////////
float vec3Length(vec3_t v)
{

	return std::sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z) );
}

vec3_t vec3Addition(vec3_t v1, vec3_t v2)
{
	vec3_t newVec3 = { (v1.x + v2.x),(v1.y + v2.y), (v1.z + v2.z) };
	return newVec3;
}


vec3_t vec3Subtraction(vec3_t v1, vec3_t v2)
{
	vec3_t newVec3 = { (v1.x - v2.x),(v1.y - v2.y), (v1.z - v2.z) };
	return newVec3;
}
vec3_t vec3Multiplication(vec3_t v, float factor)
{
	vec3_t newVec3 = { v.x * factor,v.y * factor,v.z * factor };
	return newVec3;
}

vec3_t vec3Division(vec3_t v, float factor)
{
	vec3_t newVec3 = { v.x / factor,v.y / factor,v.z / factor };
	return newVec3;
}

vec3_t vec3CrossProduct(vec3_t firstVector, vec3_t SecondVector)
{
	vec3_t normalVector =
	{
		firstVector.y * SecondVector.z - firstVector.z * SecondVector.y,
		firstVector.z * SecondVector.x - firstVector.x * SecondVector.z,
		firstVector.x * SecondVector.y - firstVector.y * SecondVector.x,

	};
	return normalVector;
}

float vec3DotProduct(vec3_t firstVector, vec3_t SecondVector)
{
	return (firstVector.x * SecondVector.x) + (firstVector.y * SecondVector.y) + (firstVector.z * SecondVector.z);

}

vec3_t vec3RotateX(vec3_t point, float angle)
{
	vec3_t rotated_vector =
	{
		point.x,
		point.y* std::cos(angle) - point.z * std::sin(angle),
		point.y* std::sin(angle) + point.z * std::cos(angle),

	};
	return rotated_vector;
}
	

vec3_t vec3RotateY(vec3_t point,float angle)
{
	vec3_t rotated_vector =
	{
		point.x* std::cos(angle) - point.z * std::sin(angle),
		point.y,
		point.x * std::sin(angle) + point.z * std::cos(angle),
	};
	return rotated_vector;
}

vec3_t vec3RotateZ(vec3_t point, float angle)
{			
	vec3_t rotated_vector =
	{
		point.x * std::cos(angle) - point.y * std::sin(angle),
		point.x * std::sin(angle) + point.y * std::cos(angle),
		point.z
	};
	return rotated_vector;
}

void vec3NormalizVector(vec3_t &vector)
{
	//getting length of vector using Pythagorean theorem
	float magnitude = std::sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);

	vector.x/= magnitude;
	vector.y/= magnitude;
	vector.z/= magnitude;
}

