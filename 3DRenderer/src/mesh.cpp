#include "mesh.h"

mesh_t mesh =
{
	{},{},{0,0,0}
};
vec3_t cubeVertices[N_CUBE_VERTICES] =
{
	{-1,-1,-1},
	{-1,1,-1},
	{1,1,-1},
	{1,-1,-1},
	{1,1,1},
	{1,-1,1},
	{-1,1,1},
	{-1,-1,1},

};

face_t cubeFaces[N_CUBE_FACES] =
{
	{1,2,3},
	{1,3,4},

	{4,3,5},
	{4,5,6},

	{6,5,7},
	{6,7,8},

	{8,7,2},
	{8,2,1},

	{2,7,5},
	{2,5,3},

	{6,8,1},
	{6,1,4},

};


void loadCubeMeshData()
{
	for (int i = 0; i < N_CUBE_FACES; i++)
	{
		face_t cubeFace = cubeFaces[i];
		mesh.faces.push_back(cubeFace);
	}
	for (int i = 0; i < N_CUBE_VERTICES; i++)
	{
		vec3_t cubeVertice = cubeVertices[i];
		mesh.vertices.push_back(cubeVertice);
	}
}