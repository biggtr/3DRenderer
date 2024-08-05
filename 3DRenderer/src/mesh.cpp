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
	{ 1,   2,  3, { 0, 0 },  { 0, 1 },  { 1, 1 },  0xFFFFFFFF },
	{ 1,   3,  4, { 0, 0 },  { 1, 1 },  { 1, 0 },  0xFFFFFFFF },
	{ 4,   3,  5, { 0, 0 },  { 0, 1 },  { 1, 1 },  0xFFFFFFFF },
	{ 4,   5,  6, { 0, 0 },  { 1, 1 },  { 1, 0 },  0xFFFFFFFF },
	{ 6,   5,  7, { 0, 0 },  { 0, 1 },  { 1, 1 },  0xFFFFFFFF },
	{ 6,   7,  8, { 0, 0 },  { 1, 1 },  { 1, 0 },  0xFFFFFFFF },

	{ 8,   7,  2, { 0, 0 },  { 0, 1 },  { 1, 1 },  0xFFFFFFFF },
	{ 8,   2,  1, { 0, 0 },  { 1, 1 },  { 1, 0 },  0xFFFFFFFF },
	{ 2,   7,  5, { 0, 0 },  { 0, 1 },  { 1, 1 },  0xFFFFFFFF },
	{ 2,   5,  3, { 0, 0 },  { 1, 1 },  { 1, 0 },  0xFFFFFFFF },
	{ 6,   8,  1, { 0, 0 },  { 0, 1 },  { 1, 1 },  0xFFFFFFFF },
	{ 6,   1,  4, { 0, 0 },  { 1, 1 },  { 1, 0 },  0xFFFFFFFF }
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

void loadObjFileData(std::string fileName)
{
	std::fstream inputFile(fileName);

	if (!inputFile.is_open())
	{
		std::cerr << "Error openning file: " << fileName << std::endl;
		return;
	}
	std::string line;
	while (std::getline(inputFile, line))
	{
		std::istringstream singleWord(line);
		char charIdentifier;
		if (!(singleWord >> charIdentifier))
		{
			std::cerr << "Error reading line: " << line << std::endl;
			continue;
		}
		if (charIdentifier == 'v')
		{
			float x, y, z;
			if (!(singleWord >> x >> y >> z))
			{
				std::cerr << "Error reading vertex from line: " << line << std::endl;
				continue;
			}
			std::cout << charIdentifier << x << y << z << std::endl;
			vec3_t vec3;
			vec3.x = x;
			vec3.y = y;
			vec3.z = z;
			mesh.vertices.push_back(vec3);
		}
		else if (charIdentifier == 'f')
		{
			int v1, t1, n1, v2, t2, n2, v3, t3, n3;
			char slash;
			if (!(singleWord >> v1 >> slash >> t1 >> slash >> n1 >>
				v2 >> slash >> t2 >> slash >> n2 >>
				v3 >> slash >> t3 >> slash >> n3))
			{
				std::cerr << "Error reading face from line: " << line << std::endl;
				continue;
			}
			std::cout << charIdentifier << v1 << v2 << v3 << std::endl;

			face_t face = { v1,v2,v3,0xFFFFFFFF };
			
			mesh.faces.push_back(face);
		}
	}


	inputFile.close();
}