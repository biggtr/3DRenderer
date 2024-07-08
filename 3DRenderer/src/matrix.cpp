#include "matrix.h"



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

