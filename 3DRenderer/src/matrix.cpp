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

mat4_t makeRotationMatrixInX(float angle)
{
	mat4_t xRotationMatrix = mat4Identity();
	xRotationMatrix.m[1][1] = std::cos(angle);
	xRotationMatrix.m[1][2] = -std::sin(angle);
	xRotationMatrix.m[2][1] = sin(angle);
	xRotationMatrix.m[2][2] = std::cos(angle);
	return xRotationMatrix;
}

mat4_t makeRotationMatrixInY(float angle)
{
	mat4_t yRotationMatrix = mat4Identity();
	yRotationMatrix.m[0][0] = std::cos(angle);
	yRotationMatrix.m[0][2] = std::sin(angle);
	yRotationMatrix.m[2][0] = -std::sin(angle);
	yRotationMatrix.m[2][2] = std::cos(angle);
	return yRotationMatrix;
}

mat4_t makeRotationMatrixInZ(float angle)
{
	mat4_t zRotationMatrix = mat4Identity();
	zRotationMatrix.m[0][0] = std::cos(angle);
	zRotationMatrix.m[0][1] = -std::sin(angle);
	zRotationMatrix.m[1][0] = std::sin(angle);
	zRotationMatrix.m[1][1] = std::cos(angle);
	return zRotationMatrix;
}

mat4_t makePerspectiveProjectionMatrix(float aspectRatio, float fieldOfView, float zNear, float zFar)
{
	float lambda = zFar / (zFar - zNear);
	mat4_t perspectiveProjectionMatrix{ {{}} };
	perspectiveProjectionMatrix.m[0][0] = aspectRatio * fieldOfView;
	perspectiveProjectionMatrix.m[1][1] = fieldOfView;
	perspectiveProjectionMatrix.m[2][2] = lambda;
	perspectiveProjectionMatrix.m[2][3] = -lambda * zNear;
	perspectiveProjectionMatrix.m[3][2] = 1.f;
	return perspectiveProjectionMatrix;
}

vec4_t matrix4MultiplyVector4(mat4_t matrix, vec4_t vector)
{
	vec4_t resultingVector;
	resultingVector.x = matrix.m[0][0] * vector.x + matrix.m[0][1] * vector.y + matrix.m[0][2] * vector.z + matrix.m[0][3] * vector.w;
	resultingVector.y = matrix.m[1][0] * vector.x + matrix.m[1][1] * vector.y + matrix.m[1][2] * vector.z + matrix.m[1][3] * vector.w;
	resultingVector.z = matrix.m[2][0] * vector.x + matrix.m[2][1] * vector.y + matrix.m[2][2] * vector.z + matrix.m[2][3] * vector.w;
	resultingVector.w = matrix.m[3][0] * vector.x + matrix.m[3][1] * vector.y + matrix.m[3][2] * vector.z + matrix.m[3][3] * vector.w;
	return resultingVector;
}

vec4_t matrix4MultiplyVector4Projection(mat4_t projectionMatrix, vec4_t vector)
{
	vec4_t result = matrix4MultiplyVector4(projectionMatrix, vector);

	//perform perspective divide with original z-value that is now stored in w in vector
	if (result.w != 0.0f)
	{
		result.x /= result.w;
		result.y /= result.w;
		result.z /= result.w;

	}
	return result;
}

mat4_t matrix4MultiplyMatrix4(mat4_t firstMatrix, mat4_t secondMatrix)
{
	mat4_t resultingMatrix;
	for (int row{}; row < 4; row++)
	{
		for (int col{}; col < 4; col++)
		{
			resultingMatrix.m[row][col] = firstMatrix.m[row][0] * secondMatrix.m[0][col] + firstMatrix.m[row][1] * secondMatrix.m[1][col] + firstMatrix.m[row][2] * secondMatrix.m[2][col] + firstMatrix.m[row][3] * secondMatrix.m[3][col];
		}
	}
	return resultingMatrix;
}

