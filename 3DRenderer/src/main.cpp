#include "display.h"
#include "vector.h"
#include "mesh.h"



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
void setup()
{
	colorBuffer = new uint32_t[windowWidth * windowHeight];

	colorBufferTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, windowWidth, windowHeight);

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
				isRunning = false;
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
	cubeRotation.y -= 0.01;
	cubeRotation.x -=0.01;
	cubeRotation.z += 0.01;

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

		vec3_t transformedVertices[3];
		// Applying transformation on each vertex of the face
		for (int j = 0; j < 3; j++)
		{
			vec3_t transformedVertex = faceVertices[j];
			transformedVertex = vec3RotateX(transformedVertex, cubeRotation.x);
			transformedVertex = vec3RotateY(transformedVertex, cubeRotation.y);
			transformedVertex = vec3RotateZ(transformedVertex, cubeRotation.z);
			
			//translate the vertices away from camera
			transformedVertex.z -= -5;

			//save vertices in an array after applying transformation
			transformedVertices[j] = transformedVertex;

		}
		// Check for back culling
		vec3_t vectorA = transformedVertices[0];
		vec3_t vectorB = transformedVertices[1];
		vec3_t vectorC = transformedVertices[2];
		
		//Get difference between vector b-a , c-a
		vec3_t vectorAB = vec3Subtraction(vectorB, vectorA);
		vec3_t vectorAC = vec3Subtraction(vectorC, vectorA);

		//Get normal value using the crossProduct between ab ac vectors
		vec3_t normal = vec3CrossProduct(vectorAB, vectorAC); // Left Handed game engine ,start with ab then ac

		//Get vector from a to camera position
		vec3_t cameraRay = vec3Subtraction(cameraPosition, vectorA);

		//Getting dot product between camera vector and normal 
		float cameraRayDotProductValue = vec3DotProduct(cameraRay, normal);


		//Checks if dot product is less than 0 then skip and dont project
		if (cameraRayDotProductValue < 0)
		{
			continue;
		}


		//Looping all 3 vertices to perform projection
		for (int j = 0; j < 3; j++)
		{
			//Project the current vertex onto the screen
			vec2_t projectedPoint = project(transformedVertices[j]);

			//scale and moving the vertex point to the middle of the screen 
			projectedPoint.x += windowWidth / 2;
			projectedPoint.y += windowHeight/ 2;
			projectedTriangle.points[j] = projectedPoint;
		}
		trianglesToRender.push_back(projectedTriangle);
	}
	

}
 
void render()
{
	clearColorBuffer(0xFF000000);
	drawGrid();
	for (int i = 0; i < trianglesToRender.size(); i++)
	{
		triangle_t triangle = trianglesToRender[i];

		drawRectangle(triangle.points[0].x, triangle.points[0].y, 4, 4, 0xFFFF0000);
		drawRectangle(triangle.points[1].x, triangle.points[1].y, 4, 4, 0xFFFF0000);
		drawRectangle(triangle.points[2].x, triangle.points[2].y, 4, 4, 0xFFFF0000);

		drawTriangle(triangle.points[0].x, triangle.points[0].y, triangle.points[1].x, triangle.points[1].y, triangle.points[2].x, triangle.points[2].y, 0xFFFF0000);
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