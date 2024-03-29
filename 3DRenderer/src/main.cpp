#include "display.h"
#include "vector.h"
#include "mesh.h"




//const int N_POINTS (9*9*9)
//vec3_t cube_points[N_POINTS];
//
//vec2_t projected_points[N_POINTS];


triangle_t trianglesToRender[N_MESH_FACES];
vec3_t cameraPosition{ 0,0,-5 };
vec3_t cubeRotation{ 0,0,0 };
int fovFactor = 640;
int previousFrameTime;
int timeToWait;
bool isRunning = false;
void setup()
{
	colorBuffer = new uint32_t[windowWidth * windowHeight];

	colorBufferTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, windowWidth, windowHeight);


}

void process_input()
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
	vec2_t projected_point = { (fovFactor * point.x) / point.z, (fovFactor * point.y) /point.z};  //fov_factor is for scaling 
	return projected_point;
}
void update()
{
	timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - previousFrameTime); // (SDL_GetTicks() - previous_frame_time) tells me how many seconds the frame took to process and store it in time to wait 
	if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME) // if time_to_wait bigger than frame_target_time  wait that much time before processing the next frame in other words checking if the cpu processed the frame fast we should delay that much time 
	{
		SDL_Delay(timeToWait);
	}
	previousFrameTime = SDL_GetTicks();
	cubeRotation.y += 0.01;
	cubeRotation.x += 0.01;
	cubeRotation.z += 0.01;


	for (int i = 0; i < N_MESH_FACES; i++)
	{
		face_t meshFace = meshFaces[i];
		vec3_t faceVertices[3];
		faceVertices[0] = meshVertices[meshFace.a - 1];
		faceVertices[1] = meshVertices[meshFace.b - 1];
		faceVertices[2] = meshVertices[meshFace.c - 1];
		triangle_t projectedTriangle;
		for (int j = 0; j < 3; j++)
		{
			vec3_t transformedVertex = faceVertices[j];
			transformedVertex = vec3_rotate_x(transformedVertex, cubeRotation.x);
			transformedVertex = vec3_rotate_y(transformedVertex, cubeRotation.y);
			transformedVertex = vec3_rotate_z(transformedVertex, cubeRotation.z);
			transformedVertex.z -= cameraPosition.z;
			vec2_t projectedPoint = project(transformedVertex);
			projectedPoint.x += windowWidth / 2;
			projectedPoint.y += windowHeight/ 2;

			projectedTriangle.points[j] = projectedPoint;
		}
		trianglesToRender[i] = projectedTriangle;
	}
	

}

void render()
{
	clear_color_buffer(0xFF000000);
	draw_grid();
	for (int i = 0; i < N_MESH_FACES; i++)
	{
		triangle_t triangle = trianglesToRender[i];
		
		draw_rectangle(triangle.points[0].x,triangle.points[0].y, 4, 4, 0xFFFF0000);
		draw_rectangle(triangle.points[1].x, triangle.points[1].y, 4, 4, 0xFFFF0000);
		draw_rectangle(triangle.points[2].x, triangle.points[2].y, 4, 4, 0xFFFF0000);

	}
	render_color_buffer();
	SDL_RenderPresent(renderer);
}



int main(int argc,char*args[])
{
	isRunning = initialize_window();

	setup();

	while (isRunning)
	{
		process_input();
		update();
		render();
	}

	destroy_window();

	std::cout << "Hello, world!";
	return 0;
}