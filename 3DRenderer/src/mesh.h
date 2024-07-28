#pragma once
#include "vector.h"
#include "triangle.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#define N_CUBE_VERTICES 8 
#define N_CUBE_FACES (6*2) // 6 faces in the cube times 2 triangles = 12



extern vec3_t cubeVertices[N_CUBE_VERTICES];
extern face_t cubeFaces[N_CUBE_FACES];

struct mesh_t
{
	std::vector<vec3_t> vertices;
	std::vector<face_t> faces;
	vec3_t rotation{};
	vec3_t scale{};
	vec3_t translation{};
	
};
extern mesh_t mesh;

//void loadCubeMeshData();
void loadObjFileData(std::string fileName);

