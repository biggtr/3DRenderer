#include "display.h"
#include "vector.h"
#include "mesh.h"
#include "triangle.h"
#include <algorithm>
#include "matrix.h"
#include <math.h>
#include "light.h"
//const int N_POINTS (9*9*9)
//vec3_t cube_points[N_POINTS];
//
//vec2_t projected_points[N_POINTS];


std::vector<triangle_t> trianglesToRender{};
vec3_t cameraPosition{ 0,0,0 };

int previousFrameTime{};
int timeToWait;
bool isRunning = false; 
mat4_t perspectiveProjectionMatrix;
RenderMethod renderMethod;
CullingMethod cullingMethod;
void setup()
{
	colorBuffer = new uint32_t[windowWidth * windowHeight];

	colorBufferTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, windowWidth, windowHeight);
	RenderMethod renderMethod = RenderMethod::WIREFRAME;
	CullingMethod cullingMethod = CullingMethod::NONE;

	float fovFactor = M_PI / 3;
	float zNear = 0.1f;
	float zFar = 100.f;
	float aspectRation = (float)windowHeight / (float)windowWidth;

	//changing the scale of the mesh
	mesh.scale.x = 1.f;
	mesh.scale.y = 1.f;
	mesh.scale.z = 1.f;

	//make perspectiveProjectionMatrix that will be multiplied with vertices to project the vertices
	perspectiveProjectionMatrix = makePerspectiveProjectionMatrix(aspectRation, fovFactor, zNear, zFar);
	//loadCubeMeshData();
	loadObjFileData("./assets/f22.obj");
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

void update()
{
	timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - previousFrameTime); // (SDL_GetTicks() - previous_frame_time) tells me how many seconds the frame took to process and store it in time to wait 
	if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME) // if time_to_wait bigger than frame_target_time  wait that much time before processing the next frame in other words checking if the cpu processed the frame fast we should delay that much time 
	{
		SDL_Delay(timeToWait);
	}
	previousFrameTime = SDL_GetTicks();

	

	
	// Change the mesh scale, rotation, and translation values per animation frame
	mesh.rotation.x += 0.001;
	mesh.rotation.y += 0.01;
	mesh.rotation.z += 0.01;
	mesh.translation.z = 5.f;


	
	//making scale matrix (used to scale objects)
	mat4_t scaleMatrix = makeScaleMatrix(mesh.scale.x, mesh.scale.y, mesh.scale.z);

	//Making rotation matrix from all the axes the will be multiplied with vertices to change their rotation
	mat4_t rotationMatrixInX = makeRotationMatrixInX(mesh.rotation.x);
	mat4_t rotationMatrixInY = makeRotationMatrixInY(mesh.rotation.y);
	mat4_t rotationMatrixInZ = makeRotationMatrixInZ(mesh.rotation.z);

	//making translation matrix that will be multiplied with vertices to change their position
	mat4_t translationMatrix = makeTranslationMatrix(mesh.translation.x, mesh.translation.y, mesh.translation.z);

	
	// Looping through all faces we have 
	for (int i = 0; i < mesh.faces.size(); i++)
	{
		face_t meshFace = mesh.faces[i];

		// Getting all vertices of each face
		vec3_t faceVertices[3];
		faceVertices[0] = mesh.vertices[meshFace.a - 1];
		faceVertices[1] = mesh.vertices[meshFace.b - 1];
		faceVertices[2] = mesh.vertices[meshFace.c - 1];


		vec4_t transformedVertices[3];
		// Applying transformation on each vertex of the face
		for (int j = 0; j < 3; j++)
		{
			vec4_t transformedVertex = vec4FromVec3(faceVertices[j]);

			
			//multiplying all matrices with world identity to get the world matrix(order matters)
			mat4_t worldMatrix = mat4Identity();
			worldMatrix = matrix4MultiplyMatrix4(scaleMatrix, worldMatrix);
			worldMatrix = matrix4MultiplyMatrix4(rotationMatrixInX, worldMatrix);
			worldMatrix = matrix4MultiplyMatrix4(rotationMatrixInY, worldMatrix);
			worldMatrix = matrix4MultiplyMatrix4(rotationMatrixInZ, worldMatrix);
			worldMatrix = matrix4MultiplyMatrix4(translationMatrix, worldMatrix);

			transformedVertex = matrix4MultiplyVector4(worldMatrix, transformedVertex);
			//save vertices in an array after applying transformation
			transformedVertices[j] = transformedVertex;

		}
		
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
		float cameraRayDotProductValue = vec3DotProduct(normal, cameraRay );

		if (cullingMethod == CullingMethod::BACKFACE_CULLING)
		{
			//Checks if dot product is less than 0 then skip and dont project
			if (cameraRayDotProductValue < 0)
			{
				continue;
			}

		}

		vec4_t projectedPoints[3];
		//Looping all 3 vertices to perform projection
		for (int j = 0; j < 3; j++)
		{
			//Project the current vertex onto the screen
			projectedPoints[j] = matrix4MultiplyVector4Projection(perspectiveProjectionMatrix, transformedVertices[j]);
			
			//scaling point into the viewport
			projectedPoints[j].x *= (windowWidth / 2.f);
			projectedPoints[j].y *= (windowHeight / 2.f);
			//inverting y axis to its original position
			projectedPoints[j].y *= -1;
			//Translate the vertex point to the middle of the screen 
			projectedPoints[j].x += (windowWidth / 2.f);
			projectedPoints[j].y += (windowHeight / 2.f);
		
		}
		// Calculate the average depth for each face based on the vertices after transformation
		float avg_depth = (transformedVertices[0].z + transformedVertices[1].z + transformedVertices[2].z) / 3.0;

		// Calculate the shade intensity based on how aliged is the face normal and the opposite of the light direction
		float lightIntensityFactor = -vec3DotProduct(normal, light.direction);

		// Calculate the triangle color based on the light angle
		uint32_t triangleColor = light_apply_intensity(meshFace.color, lightIntensityFactor);

		triangle_t projectedTriangle = {
			{
				{projectedPoints[0].x, projectedPoints[0].y },
				{projectedPoints[1].x, projectedPoints[1].y },
				{projectedPoints[2].x, projectedPoints[2].y },
			},
			triangleColor,	
			avg_depth
		};
		trianglesToRender.push_back(projectedTriangle);

		//sorting triangles based on z axis (Depth) to render triangles from back to front 
		std::sort(trianglesToRender.begin(), trianglesToRender.end(), [](const triangle_t& a, const triangle_t& b) {
			return a.avgDepth < b.avgDepth;
			});


	}
}
void render()
{
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
			drawTriangle(triangle.points[0].x, triangle.points[0].y, triangle.points[1].x, triangle.points[1].y, triangle.points[2].x, triangle.points[2].y, 0xFFFFFF00);
		
		//draws filled Triangle with color
		if(renderMethod == RenderMethod::FILL_TRIANGLE || renderMethod == RenderMethod::FILL_TRIANGLE_WIRE )
			drawFilledTriangle(triangle.points[0].x, triangle.points[0].y, triangle.points[1].x, triangle.points[1].y, triangle.points[2].x, triangle.points[2].y, triangle.color);
	}
	trianglesToRender.clear();

	renderColorBuffer();

	clearColorBuffer(0xFF000000);

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