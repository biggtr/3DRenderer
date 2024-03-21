#include "display.h"
#include "vector.h"

#define N_POINTS (9*9*9)


bool is_running = false;

vec3_t cube_points[N_POINTS];

vec2_t projected_points[N_POINTS];

vec3_t camera_position{ 0,0,-5 };
vec3_t cube_rotation{ 0,0,0 };
int fov_factor = 640;
int previous_frame_time;
void setup()
{
	color_buffer = new uint32_t[WindowWidth * WindowHeight];

	color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WindowWidth, WindowHeight);

	int points_count = 0;
	//initialize cube vector with values with 9 points in each direction x,y,z 
	for (float x = -1; x <= 1; x += 0.25) // each side is 2 size from -1 to 1  = 2; and we want to fill each with 9 points so 2/9 = 0.22
	{
		for (float y = -1; y <= 1; y += 0.25)
		{
			for (float z = -1; z <= 1; z += 0.25)
			{
				vec3_t new_point = { x,y,z };
				cube_points[points_count++] = new_point;
			}
		}
	}
}

void process_input()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
		case SDL_QUIT:
			is_running = false;
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
				is_running = false;
			break;

	}

}
vec2_t project(vec3_t point)
{
	vec2_t projected_point = { (fov_factor * point.x) / point.z, (fov_factor * point.y) /point.z};  //fov_factor is for scaling 
	return projected_point;
}
void update()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), previous_frame_time + FRAME_TARGET_TIME));

	previous_frame_time = SDL_GetTicks();
	cube_rotation.y += 0.01;
	cube_rotation.x += 0.01;
	cube_rotation.z += 0.01;

	//transform the points  and then  project the point to the 2d plane(computer screen)
	for (int i = 0; i < N_POINTS; i++)
	{
		vec3_t point = cube_points[i];
		vec3_t transformed_point = vec3_rotate_y(point, cube_rotation.y);
		transformed_point = vec3_rotate_x(transformed_point, cube_rotation.x);
		transformed_point.z -= camera_position.z;    // moving the camera from the z direction with camera_position.z units
		vec2_t projected_point = project(transformed_point);
		projected_points[i] = projected_point;
	}

}

void render()
{
	clear_color_buffer(0xFF000000);
	draw_grid();
	for (int i = 0; i < N_POINTS; i++)
	{
		vec2_t projected_point = projected_points[i];
		draw_rectangle(projected_point.x + WindowWidth /2 ,projected_point.y + WindowHeight / 2 ,4,4,0xFFFF0000);
	}
	render_color_buffer();
	SDL_RenderPresent(renderer);
}



int main(int argc,char*args[])
{
	is_running = initialize_window();

	setup();

	while (is_running)
	{
		process_input();
		update();
		render();
	}

	destroy_window();

	std::cout << "Hello, world!";
	return 0;
}