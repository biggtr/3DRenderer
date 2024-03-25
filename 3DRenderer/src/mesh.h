#pragma once
#include "vector.h"
#include "triangle.h"
#define N_MESH_VERTICES 8 
#define N_MESH_FACES (6*2) // 6 faces in the cube times 2 triangles = 12



extern vec3_t meshVertices[N_MESH_VERTICES];
extern face_t meshFaces[N_MESH_FACES];