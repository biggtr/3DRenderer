#pragma once



struct vec2_t
{
	float x, y;
};

struct vec3_t
{
	float x, y, z;
};

struct vec4_t
{
	float x, y, z, w;
};
//////////////////////////////////////////////////////////////////////////
// Vector 2 Functions 
//////////////////////////////////////////////////////////////////////////
float vec2Length(vec2_t v);
vec2_t vec2Addition(vec2_t v1, vec2_t v2);
vec2_t vec2Subtraction(vec2_t v1, vec2_t v2);
vec2_t vec2Multiplication(vec2_t v, float factor);
vec2_t vec2Division(vec2_t v, float factor);
float vec2DotProduct(vec2_t firstVector, vec2_t SecondVector);

//////////////////////////////////////////////////////////////////////////
// Vector 3 Functions
//////////////////////////////////////////////////////////////////////////
float vec3Length(vec3_t v);
vec3_t vec3Addition(vec3_t v1, vec3_t v2);
vec3_t vec3Subtraction(vec3_t v1, vec3_t v2);
vec3_t vec3Multiplication(vec3_t v, float factor);
vec3_t vec3Division(vec3_t v, float factor);
vec3_t vec3CrossProduct(vec3_t firstVector, vec3_t SecondVector);
float  vec3DotProduct(vec3_t firstVector, vec3_t SecondVector);
vec3_t vec3RotateX(vec3_t point, float angle);
vec3_t vec3RotateY(vec3_t point, float angle);
vec3_t vec3RotateZ(vec3_t point, float angle);
void vec3NormalizVector(vec3_t &vector);


//////////////////////////////////////////////////////////////////////////
// Vector 4 Functions
//////////////////////////////////////////////////////////////////////////

vec4_t vec4FromVec3(vec3_t vector);
vec3_t vec3FromVec4(vec4_t vector);