#include "display.h"
#include "vector.h"
#include "mesh.h"
#include "triangle.h"
#include <algorithm>
#include "matrix.h"
//const int N_POINTS (9*9*9)
//vec3_t cube_points[N_POINTS];
//
//vec2_t projected_points[N_POINTS];


std::vector<triangle_t> trianglesToRender{};
vec3_t cameraPosition{ 0,0,0 };
vec3_t cubeRotation{ 0,0,0 };
int fovFactor = 640;
int previousFrameTime;
int timeToWait;
bool isRunning = false; 
RenderMethod renderMethod;
CullingMethod cullingMethod;
void setup()
{
	colorBuffer = new uint32_t[windowWidth * windowHeight];

	colorBufferTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, windowWidth, windowHeight);
	RenderMethod renderMethod = RenderMethod::WIREFRAME;
	CullingMethod cullingMethod = CullingMethod::NONE;

	
	//loadCubeMeshData();
	loadObjFileData("./assets/cube.obj");
}

void processInput()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
		case SDL_QUIT:
			isRunning = false;
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				isRunning = false;
			}
			if (event.key.keysym.sym == SDLK_1)
				renderMethod = RenderMethod::WIREFRAME;
			if (event.key.keysym.sym == SDLK_2)
				renderMethod = RenderMethod::FILL_TRIANGLE;
			if (event.key.keysym.sym == SDLK_3)
				renderMethod = RenderMethod::FILL_TRIANGLE_WIRE;
			if (event.key.keysym.sym == SDLK_b)
			{	
				cullingMethod = CullingMethod::BACKFACE_CULLING;
			}
			if (event.key.keysym.sym == SDLK_c)
				cullingMethod = CullingMethod::NONE;

			break;



	}

}
vec2_t project(vec3_t point)
{
	vec2_t projectedPoint = { (fovFactor * point.x) / point.z, (fovFactor * point.y) /point.z};  //fov_factor is for scaling 
	return projectedPoint;
}
void update()
{
	timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - previousFrameTime); // (SDL_GetTicks() - previous_frame_time) tells me how many seconds the frame took to process and store it in time to wait 
	if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME) // if time_to_wait bigger than frame_target_time  wait that much time before processing the next frame in other words checking if the cpu processed the frame fast we should delay that much time 
	{
		SDL_Delay(timeToWait);
	}
	previousFrameTime = SDL_GetTicks();

	//incrementing rotation value of the mesh every frame
	

	//incrementing scale value of mesh every frame
	mesh.scale.x += 0.01;

	//making scale matrix (used to scale objs)
	mat4_t scaleMatrix = makeScaleMatrix(mesh.scale.x, mesh.scale.y, mesh.scale.z);

	// Looping thro all faces we have 
	for (int i = 0; i < mesh.faces.size(); i++)
	{
		face_t meshFace = mesh.faces[i];

		// Getting all vertices of each face
		vec3_t faceVertices[3];
		faceVertices[0] = mesh.vertices[meshFace.a - 1];
		faceVertices[1] = mesh.vertices[meshFace.b - 1];
		faceVertices[2] = mesh.vertices[meshFace.c - 1];

		triangle_t projectedTriangle;

		vec4_t transformedVertices[3];
		// Applying transformation on each vertex of the face
		for (int j = 0; j < 3; j++)
		{
			vec4_t transformedVertex = vec4FromVec3(faceVertices[j]);

			//use scale matrix to scale vertices
			transformedVertex = multiplyMatrixVector(scaleMatrix, transformedVertex);


			//translate the vertices away from camera
			transformedVertex.z -= -5;

			//save vertices in an array after applying transformation
			transformedVertices[j] = transformedVertex;

		}
		if (cullingMethod == CullingMethod::BACKFACE_CULLING)
		{
			// Check for back culling
			vec3_t vectorA = vec3FromVec4(transformedVertices[0]);
			vec3_t vectorB = vec3FromVec4(transformedVertices[1]);
			vec3_t vectorC = vec3FromVec4(transformedVertices[2]);

			//Get difference between vector b-a , c-a
			vec3_t vectorAB = vec3Subtraction(vectorB, vectorA);
			vec3_t vectorAC = vec3Subtraction(vectorC, vectorA);
			vec3NormalizVector(vectorAB);
			vec3NormalizVector(vectorAC);

			//Get normal value using the crossProduct between ab ac vectors
			vec3_t normal = vec3CrossProduct(vectorAB, vectorAC); // Left Handed game engine ,start with ab then ac

			//Normalize normal vector to get just the direction of the normal 
			vec3NormalizVector(normal);

			//Get vector from a to camera position #calculating distance between camera and position a 
			vec3_t cameraRay = vec3Subtraction(cameraPosition, vectorA);

			//Getting dot product between camera vector and normal 
			float cameraRayDotProductValue = vec3DotProduct(cameraRay, normal);


			//Checks if dot product is less than 0 then skip and dont project
			if (cameraRayDotProductValue < 0)
			{
				continue;
			}

		}


		//Looping all 3 vertices to perform projection
		for (int j = 0; j < 3; j++)
		{
			//Project the current vertex onto the screen
			vec2_t projectedPoint = project(vec3FromVec4(transformedVertices[j]));

			//scale and moving the vertex point to the middle of the screen 
			projectedPoint.x += windowWidth / 2;
			projectedPoint.y += windowHeight / 2;
			projectedTriangle.points[j] = projectedPoint;
		}
		//getting the average of all of the z vertices to sort triangles in ascending order
		projectedTriangle.avgDepth = (transformedVertices[0].z + transformedVertices[1].z + transformedVertices[2].z) / 3;

		trianglesToRender.push_back(projectedTriangle);

		//sorting triangles based on z axis (Depth) to render triangles from back to front 
		std::sort(trianglesToRender.begin(), trianglesToRender.end(), [](const triangle_t& a, const triangle_t& b) {
			return a.avgDepth < b.avgDepth;
			});


	}
}
void render()
{
	clearColorBuffer(0xFF000000);
	drawGrid();

	//renders all triangles that passed back face culling check
	for (int i = 0; i < trianglesToRender.size(); i++)
	{
		triangle_t triangle = trianglesToRender[i];

		////drawing 3 little dots expressing the triangle face 
		//drawRectangle(triangle.points[0].x, triangle.points[0].y, 4, 4, 0xFFFF0000);
		//drawRectangle(triangle.points[1].x, triangle.points[1].y, 4, 4, 0xFFFF0000);
		//drawRectangle(triangle.points[2].x, triangle.points[2].y, 4, 4, 0xFFFF0000);

		//draws unfilled Triangle (wireframe)
		if(renderMethod == RenderMethod::WIREFRAME || renderMethod == RenderMethod::FILL_TRIANGLE_WIRE)
			drawTriangle(triangle.points[0].x, triangle.points[0].y, triangle.points[1].x, triangle.points[1].y, triangle.points[2].x, triangle.points[2].y,  0xFF0000FF);
		
		//draws filled Triangle with color
		if(renderMethod == RenderMethod::FILL_TRIANGLE || renderMethod == RenderMethod::FILL_TRIANGLE_WIRE )
			drawFilledTriangle(triangle.points[0].x, triangle.points[0].y, triangle.points[1].x, triangle.points[1].y, triangle.points[2].x, triangle.points[2].y, 0xFFFFFFFF);
	}
	trianglesToRender.clear();
	renderColorBuffer();
	SDL_RenderPresent(renderer);
}



int main(int argc,char*args[])
{
	isRunning = initializeWindow();

	setup();

	while (isRunning)
	{
		processInput();
		update();
		render();
	}

	destroyWindow();

	return 0;
}